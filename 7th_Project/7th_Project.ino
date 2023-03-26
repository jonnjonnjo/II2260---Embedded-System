// Initialize all Liibrary
#include "BluetoothSerial.h"
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <Wire.h>
#include <BMx280I2C.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// for BMP
#define I2C_SDA 21
#define I2C_SCL 22
BMx280I2C bmx280(0x76);
float temperature = 0;
float pressure = 0;

// for LCD 
LiquidCrystal_I2C lcd(0x27,16,2);

BluetoothSerial SerialBT;
String message = "";
char incomingChar;
String help[] = {"LCD Display","Temperature","Pressure","Light","Show here","Print to LCD display"};

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Jon's ESP32"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  // setting up the LCD display
  lcd.begin();
  lcd.clear();         
  lcd.backlight();

  // setting up the BMP sensor
  Wire.begin(I2C_SDA, I2C_SCL);
  if (!bmx280.begin())
  {
    SerialBT.println("You can't use the BMP sensor right now.");
  }
  bmx280.resetToDefaults();
  bmx280.writeOversamplingPressure(BMx280MI::OSRS_P_x16);
  bmx280.writeOversamplingTemperature(BMx280MI::OSRS_T_x16);


}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {

    Serial.write("ASD");
  }
  delay(20);
}