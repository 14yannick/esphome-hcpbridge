#include "hcpbridge_button.h"

namespace esphome {
namespace hcpbridge {

static const char *const TAG = "hcpbridge.button";

void HCPBridgeButtonVent::press_action() {
  ESP_LOGD(TAG, "HCPBridgeButtonVent::press_action() - Triggering vent position");
  this->parent_->engine->ventilationPositionDoor();
}

void HCPBridgeButtonHalf::press_action() {
  ESP_LOGD(TAG, "HCPBridgeButtonHalf::press_action() - Triggering half-open position");
  this->parent_->engine->halfPositionDoor();
}

void HCPBridgeButtonImpulse::press_action() {
  ESP_LOGD(TAG, "HCPBridgeButtonImpulse::press_action() - Triggering impulse action");
  this->parent_->engine->impulseDoor();
}

}  // namespace hcpbridge
}  // namespace esphome
