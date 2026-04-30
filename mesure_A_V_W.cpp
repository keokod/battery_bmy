#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 16

#define INA226_ADDR 0x40

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ----------- INA226 -----------

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

float getVoltage() {
  uint16_t raw = read16(0x02);
  return raw * 1.25 / 1000.0; // volts
}

float getCurrent() {
  int16_t raw = (int16_t)read16(0x04);
  return raw * 0.0001; // calibré R100
}

// ----------- SETUP -----------

void setup() {
  Serial.begin(115200);

  Wire.begin(4, 15);

  // reset OLED
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  delay(50);
  digitalWrite(16, HIGH);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED INIT FAIL");
    while (true);
  }

  // 🔥 calibration INA226 (R100 = 0.1Ω)
  write16(0x05, 560);

  Serial.println("System ready (OLED + INA226)");

  display.clearDisplay();
}

// ----------- LOOP -----------

void loop() {
  float voltage = getVoltage();
  float current = getCurrent();
  float power = voltage * current;

  // Serial debug
  Serial.print("V=");
  Serial.print(voltage);
  Serial.print(" V | I=");
  Serial.print(current);
  Serial.print(" A | P=");
  Serial.print(power);
  Serial.println(" W");

  // OLED display
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);
  display.println("INA226 Monitor");

  display.setCursor(0, 20);
  display.print("Voltage: ");
  display.print(voltage, 2);
  display.println(" V");

  display.setCursor(0, 35);
  display.print("Current: ");
  display.print(current, 3);
  display.println(" A");

  display.setCursor(0, 50);
  display.print("Power: ");
  display.print(power, 2);
  display.println(" W");

  display.display();

  delay(1000);
}

#define SCREEN_HEIGHT 64
#define OLED_RESET 16

#define INA226_ADDR 0x40

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ----------- INA226 -----------

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

float getVoltage() {
  uint16_t raw = read16(0x02);
  return raw * 1.25 / 1000.0; // volts
}

float getCurrent() {
  int16_t raw = (int16_t)read16(0x04);
  return raw * 0.0001; // calibré R100
}

// ----------- SETUP -----------

void setup() {
  Serial.begin(115200);

  Wire.begin(4, 15);

  // reset OLED
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  delay(50);
  digitalWrite(16, HIGH);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED INIT FAIL");
    while (true);
  }

  // 🔥 calibration INA226 (R100 = 0.1Ω)
  write16(0x05, 560);

  Serial.println("System ready (OLED + INA226)");

  display.clearDisplay();
}

// ----------- LOOP -----------

void loop() {
  float voltage = getVoltage();
  float current = getCurrent();
  float power = voltage * current;

  // Serial debug
  Serial.print("V=");
  Serial.print(voltage);
  Serial.print(" V | I=");
  Serial.print(current);
  Serial.print(" A | P=");
  Serial.print(power);
  Serial.println(" W");

  // OLED display
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);
  display.println("INA226 Monitor");

  display.setCursor(0, 20);
  display.print("Voltage: ");
  display.print(voltage, 2);
  display.println(" V");

  display.setCursor(0, 35);
  display.print("Current: ");
  display.print(current, 3);
  display.println(" A");

  display.setCursor(0, 50);
  display.print("Power: ");
  display.print(power, 2);
  display.println(" W");

  display.display();

  delay(1000);
}
