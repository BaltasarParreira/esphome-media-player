#include "waveshare_backlight_output.h"

#include <algorithm>
#include <cmath>

#include "esphome/core/log.h"

namespace esphome {
namespace waveshare_backlight {

static const char *const TAG = "waveshare_backlight";

void WaveshareBacklightOutput::setup() {
  if (this->enable_pin_ != nullptr) {
    this->enable_pin_->setup();
    this->enable_pin_->pin_mode(gpio::FLAG_OUTPUT);
    this->enable_pin_->digital_write(true);
  }
}

void WaveshareBacklightOutput::dump_config() {
  ESP_LOGCONFIG(TAG, "Waveshare Backlight Output:");
  LOG_I2C_DEVICE(this);
  ESP_LOGCONFIG(TAG, "  Brightness register: 0x%02X", this->brightness_register_);
  LOG_PIN("  Enable Pin: ", this->enable_pin_);
}

void WaveshareBacklightOutput::write_state(float state) {
  const float clamped = std::max(0.0f, std::min(1.0f, state));
  const auto value = static_cast<uint8_t>(std::round(clamped * 255.0f));
  this->write_brightness_(value);
}

void WaveshareBacklightOutput::write_brightness_(uint8_t value) {
  auto err = this->write_register(this->brightness_register_, &value, 1);
  if (err != i2c::ERROR_OK) {
    ESP_LOGW(TAG, "Failed to write brightness 0x%02X to register 0x%02X: error %d", value,
             this->brightness_register_, err);
  }
}

}  // namespace waveshare_backlight
}  // namespace esphome
