from esphome import pins
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
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
    CONF_NMEA2K_DEVICE_ID,
    CONF_DEVICES,
    CONF_DEVICE_ID,
    CONF_NAME,
    CONF_PGNS
)

MULTI_CONF = True

CONF_RADSENS_ID = "nmea2k_id"

nmea2k_ns = cg.esphome_ns.namespace("nmea2k")
nmea_pgns = nmea2k_ns.enum('pgns')
PGNS = {
  "SystemTime": nmea_pgns.SYSTEMTIME,
  "AISSafetyRelatedBroadcast": nmea_pgns.AISSAFETYRELATEDBROADCAST,
  "MOBNotification": nmea_pgns.MOBNOTIFICATION,
  "HeadingTrackControl": nmea_pgns.HEADINGTRACKCONTROL,
  "Rudder": nmea_pgns.RUDDER,
  "Heading": nmea_pgns.HEADING,
  "RateOfTurn": nmea_pgns.RATEOFTURN,
  "Heave": nmea_pgns.HEAVE,
  "Additude": nmea_pgns.ADDITUDE,
  "MagneticVariation": nmea_pgns.MAGNETICVARIATION,
  "EngineParamRapid": nmea_pgns.ENGINEPARAMRAPID,
  "EngineDynamicParam": nmea_pgns.ENGINEDYNAMICPARAM,
  "TransmissionParameters": nmea_pgns.TRANSMISSIONPARAMETERS,
  "EngineTripParameters": nmea_pgns.ENGINETRIPPARAMETERS,
  "BinaryStatus": nmea_pgns.BINARYSTATUS,
  "SwitchbankControl": nmea_pgns.SWITCHBANKCONTROL,
  "FluidLevel": nmea_pgns.FLUIDLEVEL,
  "DCStatus": nmea_pgns.DCSTATUS,
  "ChargerStatus": nmea_pgns.CHARGERSTATUS,
  "DCBatStatus": nmea_pgns.DCBATSTATUS,
  "ChargerConf": nmea_pgns.CHARGERCONF,
  "BatConf": nmea_pgns.BATCONF,
  "DCConvStatus": nmea_pgns.DCCONVSTATUS,
  "DCVoltageCurrent": nmea_pgns.DCVOLTAGECURRENT,
  "Leeway": nmea_pgns.LEEWAY,
  "BoatSpeed": nmea_pgns.BOATSPEED,
  "WaterDepth": nmea_pgns.WATERDEPTH,
  "DistanceLog": nmea_pgns.DISTANCELOG,
  "PositionRapid": nmea_pgns.POSITIONRAPID,
  "COGSOGRapid": nmea_pgns.COGSOGRAPID,
  "GNSS": nmea_pgns.GNSS,
  "LocalOffset": nmea_pgns.LOCALOFFSET,
  "AISClassAPosition": nmea_pgns.AISCLASSAPOSITION,
  "AISClassBPosition": nmea_pgns.AISCLASSBPOSITION,
  "AISAtoNReport": nmea_pgns.AISATONREPORT,
  "XTE": nmea_pgns.XTE,
  "NavigationInfo": nmea_pgns.NAVIGATIONINFO,
  "GNSSDOPData": nmea_pgns.GNSSDOPDATA,
  "GNSSSatellitesInView": nmea_pgns.GNSSSATELLITESINVIEW,
  "AISClassAStatic": nmea_pgns.AISCLASSASTATIC,
  "AISClassBStaticPartA": nmea_pgns.AISCLASSBSTATICPARTA,
  "AISClassBStaticPartB": nmea_pgns.AISCLASSBSTATICPARTB,
  "WindSpeed": nmea_pgns.WINDSPEED,
  "OutsideEnvironmentalParameters": nmea_pgns.OUTSIDEENVIRONMENTALPARAMETERS,
  "EnvironmentalParameters": nmea_pgns.ENVIRONMENTALPARAMETERS,
  "Temperature": nmea_pgns.TEMPERATURE,
  "TemperatureExt": nmea_pgns.TEMPERATUREEXT,
  "Humidity": nmea_pgns.HUMIDITY,
  "Pressure": nmea_pgns.PRESSURE,
  "MeteorlogicalStationData": nmea_pgns.METEORLOGICALSTATIONDATA,
  "TrimTab": nmea_pgns.TRIMTAB,
  "DirectionData": nmea_pgns.DIRECTIONDATA,
}

Nmea2kComponent = nmea2k_ns.class_(
    "Nmea2kComponent", cg.Component 
)

SENSOR_KEYS = {
    "n2kstatus": sensor.sensor_schema(
        name="NMEA 2000 Status",
        unit_of_measurement="", 
        accuracy_decimals=0,
        icon="mdi:gauge",
        entity_category="diagnostic"
        ),
    "n2kaddress": sensor.sensor_schema(
        name="NMEA 2000 Address",
        unit_of_measurement="", 
        accuracy_decimals=0,
        icon="mdi:sign-real-estate",
        entity_category="diagnostic"
    ),
    "rx_error_counter": sensor.sensor_schema(
        name="NMEA 2000 RX Errors",
        unit_of_measurement="", 
        accuracy_decimal=0,
        icon="mdi:alert-circle",
        entity_category="diagnostic"
    ),
    "tx_error_counter": sensor.sensor_schema(
        name="NMEA 2000 TX Errors",
        unit_of_measurement="", 
        accuracy_decimals=0,
        icon="mdi:alert-circle",
        entity_category="diagnostic"
    ),
    "tx_failed": sensor.sensor_schema(
    name="NMEA 2000 TX Failures",
    unit_of_measurement="", 
    accuracy_decimals=0,
    icon="mdi:alert-circle",
    entity_category="diagnostic"
    ),
    "rx_missed": sensor.sensor_schema(
        name="NMEA 2000 RX Missed",
        unit_of_measurement="", 
        accuracy_decimals=0,
        icon="mdi:alert-circle",
        entity_category="diagnostic"
    ),
    "rx_overrun": sensor.sensor_schema(
        name="NMEA 2000 RX Overrun",
        unit_of_measurement="", 
        accuracy_decimals=0,
        entity_category="diagnostic",
        icon="mdi:alert-circle"
    ),
    "tx_timeouts": sensor.sensor_schema(
        name="NMEA 2000 TX Timeouts"
        unit_of_measurement="", 
        accuracy_decimals=0,
        entity_category="diagnostic",
        icon="mdi:alert-circle"
    )
}


DEVICE_SCHEMA = cv.Schema({
    cv.Required(CONF_NAME): cv.string,
    cv.Required(CONF_DEVICE_ID): cv.positive_int,
    cv.Required(CONF_PGNS): cv.ensure_list(cv.enum(PGNS, upper=False)),
})

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(Nmea2kComponent),
            cv.Required(CONF_CAN_TX_PIN): pins.internal_gpio_output_pin_schema,
            cv.Required(CONF_CAN_RX_PIN): pins.internal_gpio_input_pin_schema,
            cv.Required(CONF_NMEA2K_DEVICE_FUNCTION): cv.positive_int,
            cv.Required(CONF_NMEA2K_DEVICE_CLASS): cv.positive_int,
            cv.Required(CONF_NMEA2K_MANUFACTURER_ID): cv.positive_int,
            cv.Required(CONF_NMEA2K_PRODUCT_NAME): cv.string,
            cv.Required(CONF_NMEA2K_PRODUCT_LOAD): cv.positive_int,
            cv.Required(CONF_NMEA2K_PRODUCT_SERIAL): cv.positive_int,
            cv.Optional(CONF_NMEA2K_DEVICE_ID): cv.positive_int,
            cv.Optional(CONF_CAN_MSG_BUFFER_SIZE, default=32): cv.positive_int,
            cv.Optional(CONF_CAN_RX_BUFFER_SIZE, default=10): cv.positive_int,
            cv.Optional(CONF_CAN_TX_BUFFER_SIZE, default=10): cv.positive_int,
            cv.Optional(CONF_NMEA2K_PRODUCT_CODE, default=100): cv.positive_int,
            cv.Optional(CONF_NMEA2K_FIRMWARE_TYPE, default="Alpha"): cv.string,
            cv.Optional(CONF_NMEA2K_FIRMWARE_VERSION, default="0.0.0"): cv.string,
            cv.Optional(CONF_NMEA2K_CERTIFICATION, default=0xff): cv.positive_int,
            cv.Optional(CONF_NMEA2K_VERSION, default=0xffff): cv.positive_int,
            cv.Optional(CONF_NMEA2K_HEARTBEAT_PERIOD, default=5000): cv.positive_int,
            cv.Optional(CONF_CAN_RECOVERY_PERIOD, default=3000): cv.positive_int,
            cv.Optional(CONF_ESPHOME_UPDATE_PERIOD, default=500): cv.positive_int,
            cv.Optional(CONF_DEVICES): cv.ensure_list(DEVICE_SCHEMA),
            cv.Optional("sensors"): cv.Schema({
                key: SENSOR_KEYS[key] for key in SENSOR_KEYS
            })
        }
    )
)

async def to_code(config):
    cg.add_library(
        name="NMEA2000",
        repository="ttlappalainen/NMEA2000-library",
        version=None
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

    active_pgns = set()
    if CONF_DEVICES in config:
        for device in config[CONF_DEVICES]:
            name = device[CONF_NAME]
            id = device[CONF_DEVICE_ID]
            pgns = device[CONF_PGNS]
            cg.add(var.register_device(id, name, pgns))
            active_pgns.update(pgns)
    for pgn in active_pgns:
        cg.add_build_flag(f"-DNMEA2K_PGN_{pgn.upper()}")
    for key in SENSOR_KEYS:
        sens = await sensor.new_sensor(config["sensors"][key])
        cg.add(getattr(var, f"set_{key}_sensor")(sens))
