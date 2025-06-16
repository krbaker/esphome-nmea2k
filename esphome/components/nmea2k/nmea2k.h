#pragma once

#include "esphome/core/component.h"

namespace esphome {
namespace nmea2k {


class Nmea2kComponent : public Component {
  public:
    Nmea2kComponent() = default;
    void setup() override;
    void dump_config() override;
    float get_setup_priority() const override;

 protected:
};

}  // namespace nmea2k
}  // namespace esphome