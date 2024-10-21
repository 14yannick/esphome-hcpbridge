#pragma once

#include "../hcpbridge.h"
#include "esphome/components/output/binary_output.h"
#include "esphome/core/component.h"

namespace esphome {
namespace hcpbridge {

class HCPBridgeBinaryOutput : public output::BinaryOutput, public Component {
  public:
    void set_hcpbridge_parent(HCPBridge *parent) { this->parent_ = parent; }
    void write_state(bool state) override;
    void dump_config() override;
  protected:
    HCPBridge *parent_;
};
}  // namespace hcpbridge
}  // namespace esphome