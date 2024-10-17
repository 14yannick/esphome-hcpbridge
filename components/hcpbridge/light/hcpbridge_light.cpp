#include "esphome/core/log.h"
#include "hcpbridge_light.h"

namespace esphome {
namespace hcpbridge {

static const char *TAG = "hcpbridge.light";

light::LightTraits HCPBridgeLight::get_traits() {
  auto traits = light::LightTraits();
  traits.set_supported_color_modes({light::ColorMode::ON_OFF});
  return traits;
}

void HCPBridgeLight::setup() {
    //this->parent_->add_on_state_callback([this]() { this->on_event_triggered(); });
}

void HCPBridgeLight::write_state(light::LightState *state) {
  bool binary;
  state->current_values_as_binary(&binary);
  if (binary)
    this->output_->turn_on();
  else
    this->output_->turn_off();
}

void HCPBridgeLight::on_event_triggered() {
  ESP_LOGD(TAG, "HCPBridgeLight::on_event_triggered() - current_value %s", this->state_->current_values.is_on() ? "true" : "false");
  ESP_LOGD(TAG, "HCPBridgeLight::on_event_triggered() - parent_light %s", this->parent_->engine->state->lightOn ? "true" : "false");
  if (!this->parent_->engine->state->valid &&
      this->state_->current_values.is_on() != this->parent_->engine->state->lightOn) {
    //try to adjust the state of the light if it has been switched outside of the component.
    ESP_LOGD(TAG, "HCPBridgeBinaryLight::update() - state changed");
    auto call = this->state_->toggle();
    call.perform();
  }
}

void HCPBridgeLight::updateState() {
  ESP_LOGD(TAG, "HCPBridgeLight::on_event_triggered() - current_value %s", this->state_->current_values.is_on() ? "true" : "false");
  ESP_LOGD(TAG, "HCPBridgeLight::on_event_triggered() - parent_light %s", this->parent_->engine->state->lightOn ? "true" : "false");
  if (!this->parent_->engine->state->valid &&
      this->state_->current_values.is_on() != this->parent_->engine->state->lightOn) {
    //try to adjust the state of the light if it has been switched outside of the component.
    ESP_LOGD(TAG, "HCPBridgeBinaryLight::update() - new state %s", this->parent_->engine->state->lightOn ? "true" : "false");
    auto call = this->state_->toggle();
    call.perform();
  }
}

void HCPBridgeLight::dump_config(){
  ESP_LOGCONFIG(TAG, "HCPBridgeBinaryLight");
}

} //namespace hcpbridge
} //namespace esphome