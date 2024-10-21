#include "hcpbridge_binarySensor.h"

namespace esphome{
namespace hcpbridge{

static const char *const TAG = "hcpbridge.binary_sensor";

void HCPBridgeRelaySensor::setup() {
    this->parent_->add_on_state_callback([this]() { this->on_event_triggered(); });
    this->publish_state(false);
}

void HCPBridgeRelaySensor::on_event_triggered() {
    if (this->parent_->engine->state->relayOn != this->state){
        this->publish_state(this->parent_->engine->state->relayOn);
    }
}
void HCPBridgeRelaySensor::dump_config(){
    ESP_LOGCONFIG(TAG, "HCPBridgeRelaySensor");
}

void HCPBridgeIsConnected::setup() {
    this->parent_->add_on_state_callback([this]() { this->on_event_triggered(); });
    this->publish_state(false);
}

void HCPBridgeIsConnected::on_event_triggered() {
    if (this->parent_->engine->state->valid != this->state){
        this->publish_state(this->parent_->engine->state->valid);
    }
}
void HCPBridgeIsConnected::dump_config(){
    ESP_LOGCONFIG(TAG, "HCPBridgeIsConnected");
}

}
}