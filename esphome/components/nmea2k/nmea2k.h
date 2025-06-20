#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace nmea2k {


class Nmea2kComponent : public Component {
  public:
    Nmea2kComponent() = default;
    void setup() override;
    void dump_config() override;
    float get_setup_priority() const override;
    void set_can_tx_pin(GPIOPin *tx_pin);
    void set_can_rx_pin(GPIOPin *rx_pin);
    void set_nmea2k_device_function(int function);
    void set_can_recovery_period(int period);
    void set_can_msg_buffer_size(int size);
    void set_can_rx_buffer_size(int size);
    void set_can_tx_buffer_size(int size);
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
    GPIOPin *can_rx_pin_;
    GPIOPin *can_tx_pin_;
    int can_recovery_period_ = 0;
    int can_msg_buffer_size_ = 0;
    int can_rx_buffer_size_ = 0;
    int can_tx_buffer_size_ = 0;
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
};

}  // namespace nmea2k
}  // namespace esphome