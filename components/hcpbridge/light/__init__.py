from esphome.components import light, output
import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_OUTPUT_ID, CONF_OUTPUT 
from .. import hcpbridge_ns, CONF_HCPBridge_ID, HCPBridge

DEPENDENCIES = ["hcpbridge"]

HCPBridgeLight = hcpbridge_ns.class_("HCPBridgeLight", light.LightOutput, cg.PollingComponent)

CONFIG_SCHEMA = light.BINARY_LIGHT_SCHEMA.extend(
    {
        cv.GenerateID(CONF_HCPBridge_ID): cv.use_id(HCPBridge),
        cv.GenerateID(CONF_OUTPUT_ID): cv.declare_id(HCPBridgeLight),
        cv.Required(CONF_OUTPUT): cv.use_id(output.BinaryOutput),
    }
).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    light_output_var = cg.new_Pvariable(config[CONF_OUTPUT_ID])
    yield light.register_light(light_output_var, config)

    var = yield cg.get_variable(config[CONF_HCPBridge_ID])
    out = yield cg.get_variable(config[CONF_OUTPUT])
    cg.add(light_output_var.set_output(out))
    parent = yield cg.get_variable(config[CONF_HCPBridge_ID])
    cg.add(light_output_var.set_hcpbridge_parent(parent))

