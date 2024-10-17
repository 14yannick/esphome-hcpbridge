#include "hcpbridge_binarySensor.h"

namespace esphome
{
namespace hcpbridge
{

static const char *const TAG = "hcpbridge.binary_sensor";

void HCPBridgeRelaySensor::setup() {
    this->parent_->add_on_state_callback([this]() { this->on_event_triggered(); });
}

void HCPBridgeRelaySensor::on_event_triggered() {
    if (this->parent_->engine->state->relayOn != this->previousState_){
        this->previousState_ = this->parent_->engine->state->relayOn;
//        ESP_LOGD(TAG, "HCPBridgeBinarySensor::update() - %s", this->previousState_ ? "true" : "false");
        this->publish_state(this->previousState_);
    }
}
void HCPBridgeRelaySensor::dump_config(){
    ESP_LOGCONFIG(TAG, "HCPBridgeRelaySensor");
}

void HCPBridgeIsConnected::update() {
    if (this->parent_->engine->state->valid != this->previousState_){
        this->previousState_ = this->parent_->engine->state->valid;
        this->publish_state(this->previousState_);
    }
}
void HCPBridgeIsConnected::dump_config(){
    ESP_LOGCONFIG(TAG, "HCPBridgeIsConnected");
}

}
}
