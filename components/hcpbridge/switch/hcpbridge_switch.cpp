#include "hcpbridge_switch.h"

namespace esphome
{
  namespace hcpbridge
  {

    static const char *const TAG = "hcpbridge.switch";

    void HCPBridgeSwitch::setup() {
        this->parent_->add_on_state_callback([this]() { this->on_event_triggered(); });
    }

    void HCPBridgeSwitch::on_event_triggered() {
      if (this->parent_ == nullptr || this->parent_->engine == nullptr) {
        ESP_LOGW(TAG, "HCPBridgeSwitch::update() - Engine or parent is null");
        return;
      }
      if (!this->parent_->engine->state->valid)
      {
        if (!this->status_has_warning())
        {
          ESP_LOGD(TAG, "HCPBridgeSwitch::update() - state is invalid");
          this->status_set_warning();
        }
        return;
      }
      if (this->status_has_warning())
      {
        ESP_LOGD(TAG, "HCPBridgeSwitch::update() - clearing warning");
        this->status_clear_warning();
      }
      bool is_venting = this->parent_->engine->state->state == HoermannState::State::VENT;

      if (this->previousState_ != is_venting) {
        ESP_LOGD(TAG, "HCPBridgeSwitch::update() - state changed to %s", is_venting ? "VENT" : "NOT VENT");
        this->publish_state(is_venting);
        this->previousState_ = is_venting;
      }
    }

    void HCPBridgeSwitch::write_state(bool state) {
      if (state) {
        if (this->parent_->engine->state->state != HoermannState::State::VENT) {
          ESP_LOGD(TAG, "HCPBridgeSwitch::write_state() - Setting door to vent");
          this->parent_->engine->ventilationPositionDoor();
        } else {
          ESP_LOGD(TAG, "HCPBridgeSwitch::write_state() - Door already in vent state");
        }
      } else {
        if (this->parent_->engine->state->state != HoermannState::State::CLOSED) {
          ESP_LOGD(TAG, "HCPBridgeSwitch::write_state() - Closing door");
          this->parent_->engine->closeDoor();
        } else {
          ESP_LOGD(TAG, "HCPBridgeSwitch::write_state() - Door already closed");
        }
      }
    }

  }
}
