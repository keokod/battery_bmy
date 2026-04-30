#include <Arduino.h>
#include <Wire.h>

#define INA226_ADDR 0x40

void write16(uint8_t reg, uint16_t value) {
  Wire.beginTransmission(INA226_ADDR);
  Wire.write(reg);
  Wire.write(value >> 8);
  Wire.write(value & 0xFF);
  Wire.endTransmission();
}

uint16_t read16(uint8_t reg) {
  Wire.beginTransmission(INA226_ADDR);
  Wire.write(reg);
  Wire.endTransmission();

  Wire.requestFrom(INA226_ADDR, (uint8_t)2);

  return (Wire.read() << 8) | Wire.read();
}

void setup() {
  Serial.begin(115200);
  Wire.begin(4, 15);

  delay(1000);

  write16(0x05, 560); // calibration R100

  Serial.print("Calibration = ");
  Serial.println(read16(0x05));
}

void loop() {}
