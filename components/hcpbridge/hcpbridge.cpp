#include "hcpbridge.h"

namespace esphome
{
  namespace hcpbridge
  {

    void HCPBridge::setup()
    {
      int8_t rx = this->rx_pin_ == nullptr ? PIN_RXD : this->rx_pin_->get_pin();
      int8_t tx = this->tx_pin_ == nullptr ? PIN_TXD : this->tx_pin_->get_pin();
      int8_t rts = this->rts_pin_ == nullptr ? -1 : this->rts_pin_->get_pin();

      this->engine = &HoermannGarageEngine::getInstance();
      this->engine->setup(rx, tx, rts);
    }
    void HCPBridge::add_on_state_callback(std::function<void()> &&callback){
      this->state_callback_.add(std::move(callback)); 
    }

    void HCPBridge::update(){
      if (this->engine->state->changed) {
        this->engine->state->clearChanged();
        this->state_callback_.call();
      }
    }
  }
}