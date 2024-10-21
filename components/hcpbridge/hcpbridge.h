#pragma once

#include "esphome/core/component.h"
#include "esphome/core/defines.h"
#include "esphome/core/hal.h"
#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

#include "hoermann.h"

namespace esphome
{
  namespace hcpbridge
  {

    class HCPBridge : public PollingComponent
    {
      public:
        void setup() override;
        void update() override;  
        void set_tx_pin(InternalGPIOPin *tx_pin) { this->tx_pin_ = tx_pin; }
        void set_rx_pin(InternalGPIOPin *rx_pin) { this->rx_pin_ = rx_pin; }
        void set_rts_pin(InternalGPIOPin *rts_pin) { this->rts_pin_ = rts_pin; }
        HoermannGarageEngine* engine;
        void add_on_state_callback(std::function<void()> &&callback);

      protected:
        InternalGPIOPin *tx_pin_;
        InternalGPIOPin *rx_pin_;
        InternalGPIOPin *rts_pin_;
        CallbackManager<void()> state_callback_;
    };
  }
}