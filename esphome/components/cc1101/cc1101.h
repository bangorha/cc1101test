#pragma once

#include "esphome.h"
#include <SPI.h>

class CC1101Component : public Component {
 public:
  CC1101Component(uint8_t cs_pin) : cs_pin_(cs_pin) {}

  void setup() override;
  void loop() override {}

 private:
  uint8_t cs_pin_;
  void reset_radio();
  bool test_spi();
};
