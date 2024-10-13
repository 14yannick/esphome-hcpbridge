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

void HCPBridgeLight::write_state(light::LightState *state) {
  bool binary;
  state->current_values_as_binary(&binary);
  if (binary)
    this->output_->turn_on();
  else
    this->output_->turn_off();
}

void HCPBridgeLight::update() {
  if (this->state_->current_values.is_on() != this->parent_->engine->state->lightOn) {
    //try to adjust the state of the light if it has been switched outside of the component.
    ESP_LOGD(TAG, "HCPBridgeBinaryLight::update() - state changed");
    auto call = this->state_->toggle();
    call.perform();
  }
}

void HCPBridgeLight::dump_config(){
  ESP_LOGCONFIG(TAG, "HCPBridgeBinaryLight");
}

} //namespace hcpbridge
} //namespace esphome