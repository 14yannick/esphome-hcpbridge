from esphome.components import binary_sensor
import esphome.config_validation as cv
import esphome.codegen as cg
from .. import hcpbridge_ns, CONF_HCPBridge_ID, HCPBridge

DEPENDENCIES = ["hcpbridge"]

HCPBridgeBinarySensor = hcpbridge_ns.class_("HCPBridgeBinarySensor", binary_sensor.BinarySensor, cg.PollingComponent)

CONFIG_SCHEMA = (
    binary_sensor.binary_sensor_schema(HCPBridgeBinarySensor)
    .extend(
        {
            cv.GenerateID(CONF_HCPBridge_ID): cv.use_id(HCPBridge),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    var = await binary_sensor.new_binary_sensor(config)
    await cg.register_component(var, config)

    parent = await cg.get_variable(config[CONF_HCPBridge_ID])
    cg.add(var.set_hcpbridge_parent(parent))