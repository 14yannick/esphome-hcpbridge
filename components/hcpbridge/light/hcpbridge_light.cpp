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
    ESP_LOGD(TAG, "HCPBridgeLight::setup() - setup method calleds");
    this->parent_->add_on_state_callback([this]() { this->on_event_triggered(); }, TAG);
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
  if (this->parent_->engine->state->valid &&
      this->state_->current_values.is_on() != this->parent_->engine->state->lightOn) {
    // Adjust the state of the light based on the external lightOn state
    ESP_LOGD(TAG, "HCPBridgeBinaryLight::update() - adjusting state");
    if (this->parent_->engine->state->lightOn) {
      this->state_->turn_on().perform();
    } else {
      this->state_->turn_off().perform();
    }
  }
}

void HCPBridgeLight::dump_config(){
  ESP_LOGCONFIG(TAG, "HCPBridgeBinaryLight");
}

} //namespace hcpbridge
} //namespace esphome