#pragma once

#include "esphome/core/component.h"
#include "esphome/components/light/light_output.h"
#include "esphome/components/output/binary_output.h"
#include "../hcpbridge.h"

namespace esphome {
namespace hcpbridge {

class HCPBridgeLight : public light::LightOutput, public Component {
  public:
    void set_hcpbridge_parent(HCPBridge *parent) { this->parent_ = parent; }
    light::LightTraits get_traits() override;
    void set_output(output::BinaryOutput *output) { output_ = output; }
    void write_state(light::LightState *state) override;
    void setup() override;
    void on_event_triggered();
    void dump_config() override;
    void setup_state(light::LightState *state) { state_ = state; };
  protected:
    HCPBridge *parent_;
    output::BinaryOutput *output_;
    light::LightState *state_{nullptr};
};

} //namespace hcpbridge
} //namespace esphome