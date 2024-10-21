#pragma once

#include "esphome/core/component.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "../hcpbridge.h"

namespace esphome {
namespace hcpbridge {

class HCPBridgeTextSensor : public text_sensor::TextSensor, public Component {
  public:
      void set_hcpbridge_parent(HCPBridge *parent) { this->parent_ = parent; }
      void setup() override;
      void on_event_triggered();

  protected:
      HCPBridge *parent_;
      HoermannState::State previousState_;
};

}  // namespace hcpbridge
}  // namespace esphome