import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.const import (
    CONF_ID,
    CONF_RX_PIN,
    CONF_TX_PIN,
)

CONF_RTS_PIN = "rts_pin"

hcpbridge_ns = cg.esphome_ns.namespace("hcpbridge")
HCPBridge = hcpbridge_ns.class_("HCPBridge", cg.PollingComponent)

CONF_HCPBridge_ID = "hcpbridge_id"

CONFIG_SCHEMA = cv.All(
    cv.Schema({
        cv.GenerateID(): cv.declare_id(HCPBridge),
        cv.Optional(CONF_RX_PIN): pins.gpio_input_pin_schema,
        cv.Optional(CONF_TX_PIN): pins.gpio_output_pin_schema,
        cv.Optional(CONF_RTS_PIN): pins.gpio_output_pin_schema,
    }).extend(cv.polling_component_schema("500ms")),
)

async def to_code(config):
  var = cg.new_Pvariable(config[CONF_ID])
  await cg.register_component(var, config)

  if CONF_RX_PIN in config:
    rx_pin = await cg.gpio_pin_expression(config[CONF_RX_PIN])
    cg.add(var.set_rx_pin(rx_pin))
  if CONF_TX_PIN in config:
    tx_pin = await cg.gpio_pin_expression(config[CONF_TX_PIN])
    cg.add(var.set_tx_pin(tx_pin))
  if CONF_RTS_PIN in config:
    rts_pin = await cg.gpio_pin_expression(config[CONF_RTS_PIN])
    cg.add(var.set_rts_pin(rts_pin))
