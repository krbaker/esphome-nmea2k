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


}  // namespace nmea2k
}  // namespace esphome