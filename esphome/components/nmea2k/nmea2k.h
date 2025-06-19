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
    void set_can_tx_pin(GPIOPin tx_pin);
    void set_can_rx_pin(GPIOPin rx_pin);
    
 protected:
    GPIOPin *CAN_RX_PIN_;
    GPIOPin *CAN_TX_PIN_;
};

}  // namespace nmea2k
}  // namespace esphome