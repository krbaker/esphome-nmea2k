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
    CONF_NMEA2K_MANUFACTURER_ID,
    CONF_NMEA2K_DEVICE_ID
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
            cv.Required(CONF_CAN_TX_PIN): pins.internal_gpio_output_pin_schema,
            cv.Required(CONF_CAN_RX_PIN): pins.internal_gpio_input_pin_schema,
            cv.Required(CONF_NMEA2K_DEVICE_FUNCTION): cv.int_,
            cv.Required(CONF_NMEA2K_DEVICE_CLASS): cv.int_,
            cv.Required(CONF_NMEA2K_MANUFACTURER_ID): cv.int_,
            cv.Required(CONF_NMEA2K_PRODUCT_NAME): cv.string,
            cv.Required(CONF_NMEA2K_PRODUCT_LOAD): cv.int_,
            cv.Required(CONF_NMEA2K_PRODUCT_SERIAL): cv.int_,
            cv.Optional(CONF_NMEA2K_DEVICE_ID): cv.int_,
            cv.Optional(CONF_CAN_MSG_BUFFER_SIZE, default=32): cv.int_,
            cv.Optional(CONF_CAN_RX_BUFFER_SIZE, default=10): cv.int_,
            cv.Optional(CONF_CAN_TX_BUFFER_SIZE, default=10): cv.int_,
            cv.Optional(CONF_NMEA2K_PRODUCT_CODE, default=100): cv.int_,
            cv.Optional(CONF_NMEA2K_FIRMWARE_TYPE, default="Alpha"): cv.string,
            cv.Optional(CONF_NMEA2K_FIRMWARE_VERSION, default="0.0.0"): cv.string,
            cv.Optional(CONF_NMEA2K_CERTIFICATION, default=0xff): cv.int_,
            cv.Optional(CONF_NMEA2K_VERSION, default=0xffff): cv.int_,
            cv.Optional(CONF_NMEA2K_HEARTBEAT_PERIOD, default=5000): cv.int_,
            cv.Optional(CONF_CAN_RECOVERY_PERIOD, default=3000): cv.int_,
            cv.Optional(CONF_ESPHOME_UPDATE_PERIOD, default=500): cv.int_
        }
    )
)

async def to_code(config):
    cg.add_library(
        name="NMEA2000",
        repository="ttlappalainen/NMEA2000-library#v4.21.5",
        version="4.21.5",
    )
    can_tx_pin = await cg.gpio_pin_expression(config[CONF_CAN_TX_PIN])
    can_rx_pin = await cg.gpio_pin_expression(config[CONF_CAN_RX_PIN])

    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    # Configure the component
    cg.add(var.set_can_tx_pin(can_tx_pin))
    cg.add(var.set_can_rx_pin(can_rx_pin))
    cg.add(var.set_nmea2k_device_function(config[CONF_NMEA2K_DEVICE_FUNCTION]))
    cg.add(var.set_nmea2k_device_class(config[CONF_NMEA2K_DEVICE_CLASS]))
    cg.add(var.set_nmea2k_manufacturer_id(config[CONF_NMEA2K_MANUFACTURER_ID]))
    cg.add(var.set_nmea2k_product_name(config[CONF_NMEA2K_PRODUCT_NAME]))
    cg.add(var.set_nmea2k_product_load(config[CONF_NMEA2K_PRODUCT_LOAD]))
    cg.add(var.set_nmea2k_product_serial(config[CONF_NMEA2K_PRODUCT_SERIAL]))
    cg.add(var.set_can_msg_buffer_size(config[CONF_CAN_MSG_BUFFER_SIZE]))
    cg.add(var.set_can_rx_buffer_size(config[CONF_CAN_RX_BUFFER_SIZE]))
    cg.add(var.set_can_tx_buffer_size(config[CONF_CAN_TX_BUFFER_SIZE]))
    cg.add(var.set_nmea2k_product_code(config[CONF_NMEA2K_PRODUCT_CODE]))
    cg.add(var.set_nmea2k_firmware_type(config[CONF_NMEA2K_FIRMWARE_TYPE]))
    cg.add(var.set_nmea2k_firmware_version(config[CONF_NMEA2K_FIRMWARE_VERSION]))
    cg.add(var.set_nmea2k_certification(config[CONF_NMEA2K_CERTIFICATION]))
    cg.add(var.set_nmea2k_version(config[CONF_NMEA2K_VERSION]))
    cg.add(var.set_nmea2k_heartbeat_period(config[CONF_NMEA2K_HEARTBEAT_PERIOD]))
    cg.add(var.set_can_recovery_period(config[CONF_CAN_RECOVERY_PERIOD]))
    cg.add(var.set_esphome_update_period(config[CONF_ESPHOME_UPDATE_PERIOD]))
    if CONF_NMEA2K_DEVICE_ID in config:
        cg.add(var.set_nmea2k_device_id(config[CONF_NMEA2K_DEVICE_ID]))