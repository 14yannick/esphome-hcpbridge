#include "hcpbridge_textSensor.h"

namespace esphome {
namespace hcpbridge {

static const char *const TAG = "hcpbridge.text_sensor";

void HCPBridgeTextSensor::setup() {
  if (this->parent_ != nullptr) {
    this->parent_->add_on_state_callback([this]() { this->on_event_triggered(); }, TAG);
  }
}

void HCPBridgeTextSensor::on_event_triggered() {
  std::string stateText;
  if (this->parent_ != nullptr && this->parent_->engine->state->state != this->previousState_) {
    switch (this->parent_->engine->state->state) {
      case HoermannState::OPENING:
        stateText = "Opening";
        break;
      case HoermannState::MOVE_VENTING:
        stateText = "Move venting";
        break;
      case HoermannState::MOVE_HALF:
        stateText = "Move half";
        break;
      case HoermannState::CLOSING:
        stateText = "Closing";
        break;
      case HoermannState::OPEN:
        stateText = "Open";
        break;
      case HoermannState::CLOSED:
        stateText = "Closed";
        break;
      case HoermannState::STOPPED:
        stateText = "Stopped";
        break;
      case HoermannState::HALFOPEN:
        stateText = "Half open";
        break;
      case HoermannState::VENT:
        stateText = "Venting";
        break;
      default:
        stateText = "Unknown";
        break;
    }
    this->previousState_ = this->parent_->engine->state->state;
    ESP_LOGD(TAG, "HCPBridgeTextSensor::update() - %s", stateText.c_str());
    this->publish_state(stateText);
  }
}

}  // namespace hcpbridge
}  // namespace esphome
