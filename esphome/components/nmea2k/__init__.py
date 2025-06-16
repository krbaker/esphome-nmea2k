from esphome import pins
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
)

from .const import (
    CONF_CAN_TX_PIN,
    CONF_CAN_RX_PIN,
    CONF_CAN_MSG_BUFFER_SIZE,
    CONF_CAN_RX_BUFFER_SIZE,
    CONF_CAN_TX_BUFFER_SIZE,
    CONF_NMEA2K_PRODUCT_SERIAL,
    CONF_NMEA2K_PRODUCT_CODE,
    CONF_NMEA2K_PRODUCT_NAME,
    CONF_NMEA2K_PRODUCT_LOAD,
    CONF_NMEA2K_FIRMWARE_TYPE,
    CONF_NMEA2K_FIRMWARE_VERSION,
    CONF_NMEA2K_CERTIFICATION,
    CONF_NMEA2K_VERSION,
    CONF_NMEA2K_HEARTBEAT_PERIOD,
    CONF_CAN_RECOVERY_PERIOD,
    CONF_ESPHOME_UPDATE_PERIOD,
    CONF_NMEA2K_DEVICE_FUNCTION,
    CONF_NMEA2K_DEVICE_CLASS,
    CONF_NMEA2K_DEVICE_ID,
)

MULTI_CONF = True

CONF_RADSENS_ID = "nmea2k_id"

nmea2k_ns = cg.esphome_ns.namespace("nmea2k")

Nmea2kComponent = nmea2k_ns.class_(
    "Nmea2kComponent", cg.Component 
)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(Nmea2kComponent),
            cv.Required(CONF_CAN_TX_PIN): pins.gpio_output_pin_schema,
            cv.Required(CONF_CAN_RX_PIN): pins.gpio_output_pin_schema,
            cv.Required(CONF_NMEA2K_DEVICE_FUNCTION): cv.int_,
            cv.Required(CONF_NMEA2K_DEVICE_CLASS): cv.int_,
            cv.Required(CONF_NMEA2K_DEVICE_ID): cv.int_,
            cv.Required(CONF_NMEA2K_PRODUCT_NAME): cv.str_,
            cv.Required(CONF_NMEA2K_PRODUCT_LOAD): cv.int_,
            cv.Optional(CONF_CAN_MSG_BUFFER_SIZE, default=32): cv.int_,
            cv.Optional(CONF_CAN_RX_BUFFER_SIZE, default=10): cv.int_,
            cv.Optional(CONF_CAN_TX_BUFFER_SIZE, default=10): cv.int_,
            cv.Optional(CONF_NMEA2K_PRODUCT_SERIAL, default=1): cv.int_,
            cv.Optional(CONF_NMEA2K_PRODUCT_CODE, default=100): cv.int_,
            cv.Optional(CONF_NMEA2K_FIRMWARE_TYPE, default="Alpha"): cv.str_,
            cv.Optional(CONF_NMEA2K_FIRMWARE_VERSION, default="0.0.0"): cv.str_,
            cv.Optional(CONF_NMEA2K_CERTIFICATION, default=0xff): cv.int_,
            cv.Optional(CONF_NMEA2K_VERSION, default=0xffff): cv.int_,
            cv.Optional(CONF_NMEA2K_HEARTBEAT_PERIOD, default=5000): cv.int_,
            cv.Optional(CONF_CAN_RECOVERY_PERIOD, default=3000): cv.int_,
            cv.Optional(CONF_ESPHOME_UPDATE_PERIOD, default=500): cv.int_
        }
    )
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
