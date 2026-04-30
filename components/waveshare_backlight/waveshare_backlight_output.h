#pragma once

#include "esphome/components/i2c/i2c.h"
#include "esphome/components/output/float_output.h"
#include "esphome/core/component.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace waveshare_backlight {

class WaveshareBacklightOutput : public output::FloatOutput, public Component, public i2c::I2CDevice {
 public:
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::HARDWARE; }

  void set_brightness_register(uint8_t brightness_register) { this->brightness_register_ = brightness_register; }
  void set_enable_pin(InternalGPIOPin *enable_pin) { this->enable_pin_ = enable_pin; }

 protected:
  void write_state(float state) override;
  void write_brightness_(uint8_t value);

  uint8_t brightness_register_{0x96};
  InternalGPIOPin *enable_pin_{nullptr};
};

}  // namespace waveshare_backlight
}  // namespace esphome
