#pragma once

#include "esphome/core/component.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "../hcpbridge.h"

namespace esphome
{
  namespace hcpbridge
  {
    class HCPBridgeRelaySensor : public binary_sensor::BinarySensor, public PollingComponent
    {
      public:
        void set_hcpbridge_parent(HCPBridge *parent) { this->parent_ = parent; }
        void update() override;
        void dump_config() override;
      private:
        HCPBridge *parent_;
        bool previousState_ = false;
    };
    class HCPBridgeIsConnected : public binary_sensor::BinarySensor, public PollingComponent
    {
      public:
        void set_hcpbridge_parent(HCPBridge *parent) { this->parent_ = parent; }
        void update() override;
        void dump_config() override;
      private:
        HCPBridge *parent_;
        bool previousState_ = false;
    };
  }
}