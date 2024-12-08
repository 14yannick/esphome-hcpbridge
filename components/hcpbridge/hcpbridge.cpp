#include "hcpbridge.h"

namespace esphome {
namespace hcpbridge {

static const char *TAG = "hcpbridge";
void HCPBridge::setup() {
  int8_t rx = this->rx_pin_ == nullptr ? PIN_RXD : this->rx_pin_->get_pin();
  int8_t tx = this->tx_pin_ == nullptr ? PIN_TXD : this->tx_pin_->get_pin();
  int8_t rts = this->rts_pin_ == nullptr ? -1 : this->rts_pin_->get_pin();

  this->engine = &HoermannGarageEngine::getInstance();
  this->engine->setup(rx, tx, rts);
}
void HCPBridge::add_on_state_callback(std::function<void()> &&callback, const char *tag) {
  auto wrapped_callback = [callback, tag]() {
    auto start = millis();
    callback();
    auto end = millis();
    ESP_LOGD(TAG, "Callback executed in %u ms [Tag: %s]", end - start, tag);
  };
  this->state_callback_.add(std::move(wrapped_callback));
}

void HCPBridge::update() {
  if (this->engine->state->changed) {
    this->engine->state->clearChanged();
    this->state_callback_.call();
  }
}
}  // namespace hcpbridge
}  // namespace esphome