#include "hcpbridge_switch.h"

namespace esphome {
namespace hcpbridge {

static const char *const TAG = "hcpbridge.switch";
static const char *const TAG2 = "hcpbridge.switch2";

// Implementation for HCPBridgeSwitchVent

void HCPBridgeSwitchVent::setup() {
    this->parent_->add_on_state_callback([this]() { this->on_event_triggered(); }, TAG);
}

void HCPBridgeSwitchVent::on_event_triggered() {
  if (this->parent_ == nullptr || this->parent_->engine == nullptr) {
    ESP_LOGW(TAG, "HCPBridgeSwitchVent::update() - Engine or parent is null");
    return;
  }
  if (!this->parent_->engine->state->valid) {
    if (!this->status_has_warning()) {
      ESP_LOGD(TAG, "HCPBridgeSwitchVent::update() - state is invalid");
      this->status_set_warning();
    }
    return;
  }
  if (this->status_has_warning()) {
    ESP_LOGD(TAG, "HCPBridgeSwitchVent::update() - clearing warning");
    this->status_clear_warning();
  }
  bool is_venting = this->parent_->engine->state->state == HoermannState::State::VENT;

  if (this->previousState_ != is_venting) {
    ESP_LOGD(TAG, "HCPBridgeSwitchVent::update() - state changed to %s", is_venting ? "VENT" : "NOT VENT");
    this->publish_state(is_venting);
    this->previousState_ = is_venting;
  }
}

void HCPBridgeSwitchVent::write_state(bool state) {
  if (state) {
    if (this->parent_->engine->state->state != HoermannState::State::VENT) {
      ESP_LOGD(TAG, "HCPBridgeSwitchVent::write_state() - Setting door to vent");
      this->parent_->engine->ventilationPositionDoor();
    } else {
      ESP_LOGD(TAG, "HCPBridgeSwitchVent::write_state() - Door already in vent state");
    }
  } else {
    if (this->parent_->engine->state->state != HoermannState::State::CLOSED) {
      ESP_LOGD(TAG, "HCPBridgeSwitchVent::write_state() - Closing door");
      this->parent_->engine->closeDoor();
    } else {
      ESP_LOGD(TAG, "HCPBridgeSwitchVent::write_state() - Door already closed");
    }
  }
}

// Implementation for HCPBridgeSwitchHalf

void HCPBridgeSwitchHalf::setup() {
    this->parent_->add_on_state_callback([this]() { this->on_event_triggered(); }, TAG2);
}

void HCPBridgeSwitchHalf::on_event_triggered() {
  if (this->parent_ == nullptr || this->parent_->engine == nullptr) {
    ESP_LOGW(TAG, "HCPBridgeSwitchHalf::update() - Engine or parent is null");
    return;
  }
  if (!this->parent_->engine->state->valid) {
    if (!this->status_has_warning()) {
      ESP_LOGD(TAG, "HCPBridgeSwitchHalf::update() - state is invalid");
      this->status_set_warning();
    }
    return;
  }
  if (this->status_has_warning()) {
    ESP_LOGD(TAG, "HCPBridgeSwitchHalf::update() - clearing warning");
    this->status_clear_warning();
  }
  bool is_half_open = this->parent_->engine->state->state == HoermannState::State::HALFOPEN;

  if (this->previousState_ != is_half_open) {
    ESP_LOGD(TAG, "HCPBridgeSwitchHalf::update() - state changed to %s", is_half_open ? "HALF OPEN" : "NOT HALF OPEN");
    this->publish_state(is_half_open);
    this->previousState_ = is_half_open;
  }
}

void HCPBridgeSwitchHalf::write_state(bool state) {
  if (state) {
    if (this->parent_->engine->state->state != HoermannState::State::HALFOPEN) {
      ESP_LOGD(TAG, "HCPBridgeSwitchHalf::write_state() - Setting door to half open");
      this->parent_->engine->halfPositionDoor();
    } else {
      ESP_LOGD(TAG, "HCPBridgeSwitchHalf::write_state() - Door already in half open state");
    }
  } else {
    if (this->parent_->engine->state->state != HoermannState::State::CLOSED) {
      ESP_LOGD(TAG, "HCPBridgeSwitchHalf::write_state() - Closing door");
      this->parent_->engine->closeDoor();
    } else {
      ESP_LOGD(TAG, "HCPBridgeSwitchHalf::write_state() - Door already closed");
    }
  }
}

}  // namespace hcpbridge
}  // namespace esphome
