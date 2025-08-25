#include "cc1101.h"

void CC1101Component::setup() {
  // Initialize SPI and CS pin
  pinMode(cs_pin_, OUTPUT);
  digitalWrite(cs_pin_, HIGH);

  SPI.begin(D5, D6, D7, cs_pin_);  // CLK, MISO, MOSI, CS

  // Reset CC1101
  reset_radio();

  // Test SPI communication
  if (test_spi()) {
    ESP_LOGW("cc1101", "SPI OK");
  } else {
    ESP_LOGE("cc1101", "SPI FAILED");
  }
}

void CC1101Component::reset_radio() {
  // Pull CS low then high to reset
  digitalWrite(cs_pin_, LOW);
  delay(1);
  digitalWrite(cs_pin_, HIGH);
  delay(1);
}

bool CC1101Component::test_spi() {
  // Simple read/write test: read part of a CC1101 register
  digitalWrite(cs_pin_, LOW);
  SPI.transfer(0x30);  // Example register address (NOP or IOCFG2)
  uint8_t result = SPI.transfer(0x00);
  digitalWrite(cs_pin_, HIGH);

  // Log the value read
  ESP_LOGI("cc1101", "Read 0x%02X from CC1101 register", result);

  // Basic check (non-zero is okay for demonstration)
  return (result != 0x00);
}
