import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import (
    CONF_ID,
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
        }
    )
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
