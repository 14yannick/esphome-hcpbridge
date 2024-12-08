#include "hcpbridge_cover.h"

namespace esphome {
namespace hcpbridge {
static const char *const TAG = "hcpbridge.cover";

void HCPBridgeCover::on_go_to_open() {
  ESP_LOGD(TAG, "HCPBridgeCover::on_go_to_open() - opening");
  this->parent_->engine->openDoor();
}

void HCPBridgeCover::on_go_to_close() {
  ESP_LOGD(TAG, "HCPBridgeCover::on_go_to_close() - closing");
  this->parent_->engine->closeDoor();
}

void HCPBridgeCover::on_go_to_half() {
  ESP_LOGD(TAG, "HCPBridgeCover::on_go_to_half() - half opening");
  this->parent_->engine->halfPositionDoor();
}

void HCPBridgeCover::on_go_to_vent() {
  ESP_LOGD(TAG, "HCPBridgeCover::on_go_to_vent() - venting");
  this->parent_->engine->ventilationPositionDoor();
}

cover::CoverTraits HCPBridgeCover::get_traits() {
  auto traits = cover::CoverTraits();
  traits.set_is_assumed_state(false);
  traits.set_supports_position(true);
  traits.set_supports_tilt(false);
  traits.set_supports_stop(true);
  traits.set_supports_toggle(true);
  return traits;
}

void HCPBridgeCover::control(const cover::CoverCall &call) {
  if (call.get_stop()) {
    this->parent_->engine->stopDoor();
  }
  if (call.get_position().has_value()) {
    if (call.get_position().value() == 1.0f) {
      this->parent_->engine->openDoor();
    } else if (call.get_position().value() == 0.0f) {
      this->parent_->engine->closeDoor();
    } else {
      this->parent_->engine->setPosition(call.get_position().value() * 100.0f);
    }
  }
  if (call.get_toggle()) {
    this->parent_->engine->impulseDoor();
  }
}

void HCPBridgeCover::setup() {
  ESP_LOGD(TAG, "HCPBridgeCover::setup() - setup method calleds");
  this->parent_->add_on_state_callback([this]() { this->on_event_triggered(); }, TAG);
}

void HCPBridgeCover::on_event_triggered() {
  if (!this->parent_->engine->state->valid) {
    if (!this->status_has_warning()) {
      ESP_LOGD(TAG,
               "HCPBridgeCover::on_event_triggered() - state is invalid, "
               "setting warning");
      this->status_set_warning();
    }
    return;
  }

  if (this->status_has_warning()) {
    ESP_LOGD(TAG, "HCPBridgeCover::on_event_triggered() - clearing warning");
    this->status_clear_warning();
  }

  HoermannState *state = this->parent_->engine->state;
  float currentPosition = state->currentPosition;
  HoermannState::State stateValue = state->state;

  // Determine current operation based on state and position
  switch (stateValue) {
    case HoermannState::OPENING:
      this->current_operation = cover::COVER_OPERATION_OPENING;
      break;
    case HoermannState::MOVE_VENTING:
    case HoermannState::MOVE_HALF:
      if (this->previousPosition_ > currentPosition) {
        this->current_operation = cover::COVER_OPERATION_OPENING;
      } else {
        this->current_operation = cover::COVER_OPERATION_CLOSING;
      }
      break;
    case HoermannState::CLOSING:
      this->current_operation = cover::COVER_OPERATION_CLOSING;
      break;
    default:
      this->current_operation = cover::COVER_OPERATION_IDLE;
      break;
  }

  this->position = currentPosition;

  bool position_changed = this->previousPosition_ != this->position;
  bool operation_changed = this->previousOperation_ != this->current_operation;

  if (operation_changed) {
    ESP_LOGV(TAG, "Operation changed: %d", this->current_operation);
    this->publish_state();  // Full publish on operation change
    this->previousOperation_ = this->current_operation;
  } else if (position_changed) {
    ESP_LOGV(TAG, "Position changed: %f", this->position);
    this->publish_state(false);  // Partial publish on position change
  }

  if (position_changed) {
    this->previousPosition_ = this->position;
  }
}
}  // namespace hcpbridge
}  // namespace esphome
