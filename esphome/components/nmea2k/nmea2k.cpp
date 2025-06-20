#include "nmea2k.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"
#include "esphome/core/datatypes.h"
#include "esphome/core/helpers.h"


namespace esphome {
namespace nmea2k {

static const char *const TAG = "nmea2k";

void Nmea2kComponent::setup() {
  ESP_LOGCONFIG(TAG, "Nmea2k Setup: starting...");
  ESP_LOGCONFIG(TAG, "Nmea2k Setup: Complete...");
}

void Nmea2kComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "Nmea2k Config:");
}

float Nmea2kComponent::get_setup_priority() const { return setup_priority::DATA; }

void Nmea2kComponent::set_can_tx_pin(GPIOPin *tx_pin) {
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting CAN TX pin to %s", tx_pin.get_name().c_str());
  this->can_tx_pin_ = tx_pin;
}

void Nmea2kComponent::set_can_rx_pin(GPIOPin *rx_pin) {
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting CAN RX pin to %s", rx_pin.get_name().c_str());
  this->can_rx_pin_ = rx_pin;
}

void Nmea2kComponent::set_nmea2k_device_function(int function) {
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting device function to %d", function);
  this->nmea2k_device_function_ = function;
}

void Nmea2kComponent::set_can_recovery_period(int period){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting CAN recovery period to %d ms", period);
  this->can_recovery_period_ = period;
}

void Nmea2kComponent::set_can_msg_buffer_size(int size){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting CAN message buffer size to %d", size);
  this->can_msg_buffer_size_ = size;
}

void Nmea2kComponent::set_can_rx_buffer_size(int size){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting CAN RX buffer size to %d", size);
  this->can_rx_buffer_size_ = size;
}

void Nmea2kComponent::set_can_tx_buffer_size(int size){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting CAN TX buffer size to %d", size);
  this->can_tx_buffer_size_ = size;
}

void Nmea2kComponent::set_nmea2k_device_class(int device_class){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting device class to %d", class);
  this->nmea2k_device_class_ = device_class;
}

void Nmea2kComponent::set_nmea2k_manufacturer_id(int id){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting manufacturer ID to %d", id);
  this->nmea2k_manufacturer_id_ = id;
}

void Nmea2kComponent::set_nmea2k_product_load(int load){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting product load to %d", load);
  this->nmea2k_product_load_ = load;
}

void Nmea2kComponent::set_nmea2k_product_serial(int serial){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting product serial to %d", serial);
  this->nmea2k_product_serial_ = serial;
}

void Nmea2kComponent::set_nmea2k_product_code(int code){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting product code to %d", code);
  this->nmea2k_product_code_ = code;
}

void Nmea2kComponent::set_nmea2k_certification(int cerfication){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting certification to %d", cerfication);
  this->nmea2k_certification_ = cerfication;
}

void Nmea2kComponent::set_nmea2k_version(int version){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting version to %d", version);
  this->nmea2k_version_ = version;
}

void Nmea2kComponent::set_nmea2k_heartbeat_period(int period){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting heartbeat period to %d ms", period);
  this->nmea2k_heartbeat_period_ = period;
}

void Nmea2kComponent::set_nmea2k_product_name(std::string name){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting product name to %s", name.c_str());
  this->nmea2k_product_name_ = name;
}

void Nmea2kComponent::set_nmea2k_firmware_type(std::string type){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting firmware type to %s", type.c_str());
  this->nmea2k_firmware_type_ = type;
}

void Nmea2kComponent::set_nmea2k_firmware_version(std::string version){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting firmware version to %s", version.c_str());
  this->nmea2k_firmware_version_ = version;
}

void Nmea2kComponent::set_esphome_update_period(int period){
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting ESPHome update period to %d ms", period);
  this->esphome_update_period_ = period;
}
      


}  // namespace nmea2k
}  // namespace esphome