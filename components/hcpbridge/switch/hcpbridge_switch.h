#pragma once

#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"
#include "../hcpbridge.h"

namespace esphome{
namespace hcpbridge{
class HCPBridgeSwitch : public switch_::Switch, public Component
{
  public:
    void set_hcpbridge_parent(HCPBridge *parent) { this->parent_ = parent; }
    void setup() override;
    void on_event_triggered();
    void write_state(bool state) override;
    bool previousState_ = false;
  protected:
    HCPBridge *parent_;
};
}
}