#pragma once

#include "esphome/core/component.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "../hcpbridge.h"

namespace esphome{
namespace hcpbridge{
class HCPBridgeRelaySensor : public binary_sensor::BinarySensor, public Component{
  public:
    void set_hcpbridge_parent(HCPBridge *parent) { this->parent_ = parent; }
    void setup() override;
    void on_event_triggered();
    void dump_config() override;
  protected:
    HCPBridge *parent_;
};
class HCPBridgeIsConnected : public binary_sensor::BinarySensor, public Component{
  public:
    void set_hcpbridge_parent(HCPBridge *parent) { this->parent_ = parent; }
    void setup() override;
    void on_event_triggered();
    void dump_config() override;
  protected:
    HCPBridge *parent_;
};
}
}