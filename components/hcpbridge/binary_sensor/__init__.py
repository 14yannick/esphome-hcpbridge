from esphome.components import binary_sensor
import esphome.config_validation as cv
import esphome.codegen as cg
from .. import hcpbridge_ns, CONF_HCPBridge_ID, HCPBridge

DEPENDENCIES = ["hcpbridge"]

HCPBridgeBinarySensor = hcpbridge_ns.class_("HCPBridgeBinarySensor", binary_sensor.BinarySensor, cg.PollingComponent)
HCPBridgeIsConnected = hcpbridge_ns.class_("HCPBridgeIsConnected", binary_sensor.BinarySensor, cg.PollingComponent)
HCPBridgeRelaySensor = hcpbridge_ns.class_("HCPBridgeRelaySensor", binary_sensor.BinarySensor, cg.PollingComponent)

CONF_IS_CONNECTED = "is_connected"
CONF_RELAY_STATE = "relay_state"


CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_HCPBridge_ID): cv.use_id(HCPBridge),
        cv.Optional(CONF_IS_CONNECTED): binary_sensor.binary_sensor_schema(
            HCPBridgeIsConnected,
        ),
        cv.Optional(CONF_RELAY_STATE): binary_sensor.binary_sensor_schema(
            HCPBridgeRelaySensor,
        ),
    }
)

async def to_code(config):
    parent = await cg.get_variable(config[CONF_HCPBridge_ID])
    if conf := config.get(CONF_IS_CONNECTED):
        con_sens = await binary_sensor.new_binary_sensor(config[CONF_IS_CONNECTED])
        await cg.register_component(con_sens, config[CONF_IS_CONNECTED])
        cg.add(con_sens.set_hcpbridge_parent(parent))
    if conf := config.get(CONF_RELAY_STATE):
        relay_sens = await binary_sensor.new_binary_sensor(config[CONF_RELAY_STATE])
        await cg.register_component(relay_sens, config[CONF_RELAY_STATE])
        cg.add(relay_sens.set_hcpbridge_parent(parent))