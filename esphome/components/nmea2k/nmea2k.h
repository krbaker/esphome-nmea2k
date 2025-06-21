#ifndef _NMEA2K_H
#define _NMEA2K_H

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"

#include "Nmea2kTwai.h"
#include "N2kTypes.h"
#include "N2kMessages.h"
#include "NMEA2000.h"


namespace esphome {
namespace nmea2k {


class Nmea2kComponent : public Component {
  public:
    Nmea2kComponent() = default;
    void setup() override;
    void loop() override;
    void dump_config() override;
    void set_id_from_mac();
    float get_setup_priority() const override;
    void set_can_tx_pin(InternalGPIOPin *tx_pin);
    void set_can_rx_pin(InternalGPIOPin *rx_pin);
    void set_nmea2k_device_function(int function);
    void set_can_recovery_period(int period);
    void set_can_msg_buffer_size(int size);
    void set_can_rx_buffer_size(int size);
    void set_can_tx_buffer_size(int size);
    void set_nmea2k_device_id(uint32_t id);
    void set_nmea2k_device_class(int device_class);
    void set_nmea2k_manufacturer_id(int id);
    void set_nmea2k_product_load(int load);
    void set_nmea2k_product_serial(int serial);
    void set_nmea2k_product_code(int code);
    void set_nmea2k_certification(int cerfication);
    void set_nmea2k_version(int version);
    void set_nmea2k_heartbeat_period(int period);
    void set_nmea2k_product_name(std::string name);
    void set_nmea2k_firmware_type(std::string type);
    void set_nmea2k_firmware_version(std::string version);
    void set_esphome_update_period(int period);
    
 protected:
    InternalGPIOPin *can_rx_pin_;
    InternalGPIOPin *can_tx_pin_;
    unsigned long can_recovery_period_ = 0;
    int can_msg_buffer_size_ = 0;
    int can_rx_buffer_size_ = 0;
    int can_tx_buffer_size_ = 0;
    uint32_t nmea2k_device_id_ = 0;
    int nmea2k_device_function_ = 0;
    int nmea2k_device_class_ = 0;
    int nmea2k_manufacturer_id_ = 0;
    int nmea2k_product_load_ = 0;
    int nmea2k_product_serial_ = 0;
    int nmea2k_product_code_ = 0;
    int nmea2k_certification_ = 0;
    int nmea2k_version_ = 0;
    int nmea2k_heartbeat_period_ = 0;
    std::string nmea2k_product_name_ = "";
    std::string nmea2k_firmware_type_ = "";
    std::string nmea2k_firmware_version_ = "";
    int esphome_update_period_ = 0;
    Nmea2kTwai *n2k;
    int NodeAddress = 32;
};

}  // namespace nmea2k
}  // namespace esphome

#endif