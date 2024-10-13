#include "hcpbridge_binarySensor.h"

namespace esphome
{
namespace hcpbridge
{

static const char *const TAG = "hcpbridge.binary_sensor";

void HCPBridgeBinarySensor::update() {
    if (this->parent_->engine->state->relayOn != this->previousState_){
        this->previousState_ = this->parent_->engine->state->relayOn;
//        ESP_LOGD(TAG, "HCPBridgeBinarySensor::update() - %s", this->previousState_ ? "true" : "false");
        this->publish_state(this->previousState_);
    }
}
void HCPBridgeBinarySensor::dump_config(){
    ESP_LOGCONFIG(TAG, "HCPBridgeBinarySensor");
}

}
}
