from esphome.components import switch
import esphome.config_validation as cv
import esphome.codegen as cg
from .. import hcpbridge_ns, CONF_HCPBridge_ID, HCPBridge

DEPENDENCIES = ["hcpbridge"]

# Rename existing switch
HCPBridgeSwitchVent = hcpbridge_ns.class_("HCPBridgeSwitchVent", switch.Switch, cg.Component)
HCPBridgeSwitchHalf = hcpbridge_ns.class_("HCPBridgeSwitchHalf", switch.Switch, cg.Component)

CONF_SWITCH_VENT = "vent_switch"
CONF_SWITCH_HALF = "half_switch"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_HCPBridge_ID): cv.use_id(HCPBridge),
        cv.Optional(CONF_SWITCH_VENT): switch.switch_schema(
            HCPBridgeSwitchVent, icon="mdi:hvac"
        ),
        cv.Optional(CONF_SWITCH_HALF): switch.switch_schema(
            HCPBridgeSwitchHalf, icon="mdi:fraction-one-half"
        ),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    parent = await cg.get_variable(config[CONF_HCPBridge_ID])

    if conf := config.get(CONF_SWITCH_VENT):
        vent_switch = await switch.new_switch(conf)
        await cg.register_component(vent_switch, conf)
        cg.add(vent_switch.set_hcpbridge_parent(parent))

    if conf := config.get(CONF_SWITCH_HALF):
        half_switch = await switch.new_switch(conf)
        await cg.register_component(half_switch, conf)
        cg.add(half_switch.set_hcpbridge_parent(parent))
