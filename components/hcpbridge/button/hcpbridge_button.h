#pragma once

#include "esphome/core/component.h"
#include "esphome/components/button/button.h"
#include "../hcpbridge.h"

namespace esphome {
namespace hcpbridge {

class HCPBridgeButtonVent : public button::Button, public Component {
  public:
    void set_hcpbridge_parent(HCPBridge *parent) { this->parent_ = parent; }
    void press_action() override;

  protected:
    HCPBridge *parent_;
};

class HCPBridgeButtonHalf : public button::Button, public Component {
  public:
    void set_hcpbridge_parent(HCPBridge *parent) { this->parent_ = parent; }
    void press_action() override;

  protected:
    HCPBridge *parent_;
};

class HCPBridgeButtonImpulse : public button::Button, public Component {
  public:
    void set_hcpbridge_parent(HCPBridge *parent) { this->parent_ = parent; }
    void press_action() override;

  protected:
    HCPBridge *parent_;
};

}  // namespace hcpbridge
}  // namespace esphome
