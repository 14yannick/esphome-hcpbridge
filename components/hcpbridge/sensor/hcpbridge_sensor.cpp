#include "hcpbridge_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace hcpbridge {

static const char *TAG = "hcpbridge.sensor";

void HCPBridgeSensor::setup() {
  this->parent_->add_on_state_callback([this]() { this->on_event_triggered(); }, TAG);
  this->update_state(0.0f);
}

void HCPBridgeSensor::dump_config() { ESP_LOGCONFIG(TAG, "HCPBridge Sensor:"); }

void HCPBridgeSensor::update_state(float value) {
  this->publish_state(value * 100);
  this->previousPosition_ = value;
  ESP_LOGD(TAG, "Published new state: %.2f", value);
}

void HCPBridgeSensor::on_event_triggered() {
  float current_position = this->parent_->engine->state->currentPosition;
  
  if (this->previousPosition_ != current_position) {
    ESP_LOGD(TAG, "Position changed: %.2f -> %.2f", this->previousPosition_, current_position);
    this->update_state(current_position);
  }
}

}  // namespace hcpbridge
}  // namespace esphome
