#include "hcpbridge_switch.h"

namespace esphome
{
  namespace hcpbridge
  {

    static const char *const TAG = "hcpbridge.switch";

    void HCPBridgeSwitch::update()
    {
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
      if (this->previousState_ != this->parent_->engine->state->state == HoermannState::VENT)
      {
        ESP_LOGD(TAG, "HCPBridgeSwitch::update() - state changed");
        this->publish_state(this->parent_->engine->state->state == HoermannState::VENT);
        this->previousState_ = this->parent_->engine->state->state == HoermannState::VENT;
      }
    }

    void HCPBridgeSwitch::write_state(bool state)
    {
      if (state)
      {
        if (this->parent_->engine->state->state != HoermannState::VENT)
        {
          ESP_LOGD(TAG, "HCPBridgeSwitch::write_state() - set to vent");
          this->parent_->engine->ventilationPositionDoor();
        }
        else
        {
          ESP_LOGD(TAG, "HCPBridgeSwitch::write_state() - Door already in vent state");
        }
      }
      else
      {
        if (this->parent_->engine->state->state != HoermannState::CLOSED)
        {
          ESP_LOGD(TAG, "HCPBridgeSwitch::write_state() - stop venting");
          this->parent_->engine->closeDoor();
        }
        else
        {
          ESP_LOGD(TAG, "HCPBridgeSwitch::write_state() - Door already in vent state");
        }
      }
    }

  }
}
