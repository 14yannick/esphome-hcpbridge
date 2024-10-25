from esphome.components import button
from esphome.const import ICON_FAN
import esphome.config_validation as cv
import esphome.codegen as cg
from .. import hcpbridge_ns, CONF_HCPBridge_ID, HCPBridge

DEPENDENCIES = ["hcpbridge"]

# Refactor existing button
HCPBridgeButtonVent = hcpbridge_ns.class_("HCPBridgeButtonVent", button.Button, cg.Component)
HCPBridgeButtonHalf = hcpbridge_ns.class_("HCPBridgeButtonHalf", button.Button, cg.Component)
HCPBridgeButtonImpulse = hcpbridge_ns.class_("HCPBridgeButtonImpulse", button.Button, cg.Component) 

CONF_BUTTON_VENT = "vent_button"
CONF_BUTTON_HALF = "half_button"
CONF_BUTTON_IMPULSE = "impulse_button"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_HCPBridge_ID): cv.use_id(HCPBridge),
        cv.Optional(CONF_BUTTON_VENT): button.button_schema(
            HCPBridgeButtonVent, icon=ICON_FAN
        ),
        cv.Optional(CONF_BUTTON_HALF): button.button_schema(
            HCPBridgeButtonHalf, icon="mdi:fraction-one-half"
        ),
        cv.Optional(CONF_BUTTON_IMPULSE): button.button_schema(
            HCPBridgeButtonImpulse, icon="mdi:arrow-up-down"
        ),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    parent = await cg.get_variable(config[CONF_HCPBridge_ID])

    if conf := config.get(CONF_BUTTON_VENT):
        vent_button = await button.new_button(conf)
        await cg.register_component(vent_button, conf)
        cg.add(vent_button.set_hcpbridge_parent(parent))

    if conf := config.get(CONF_BUTTON_HALF):
        half_button = await button.new_button(conf)
        await cg.register_component(half_button, conf)
        cg.add(half_button.set_hcpbridge_parent(parent))

    if conf := config.get(CONF_BUTTON_IMPULSE):
        impulse_button = await button.new_button(conf)
        await cg.register_component(impulse_button, conf)
        cg.add(impulse_button.set_hcpbridge_parent(parent))
