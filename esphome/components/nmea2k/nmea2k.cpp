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
  this->CAN_TX_PIN_ = tx_pin;
}

void Nmea2kComponent::set_can_rx_pin(GPIOPin *rx_pin) {
  ESP_LOGCONFIG(TAG, "Nmea2k: Setting CAN RX pin to %s", rx_pin.get_name().c_str());
  this->CAN_RX_PIN_ = rx_pin;
}


}  // namespace nmea2k
}  // namespace esphome