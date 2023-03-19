#include <Arduino.h>
#include <Wire.h>

#define I2C_SDA 21
#define I2C_SCL 22

#include <BMx280I2C.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDRESS 0x76

//create a BMx280I2C object using the I2C interface with I2C Address 0x76
BMx280I2C bmx280(I2C_ADDRESS);
LiquidCrystal_I2C lcd(0x27,16,2);

// declaring the variable
float temperature = 0;
float pressure = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //  Wire.begin();
  Wire.begin(I2C_SDA, I2C_SCL);


  //begin() checks the Interface, reads the sensor ID (to differentiate between BMP280 and BME280)
  //and reads compensation parameters.
  if (!bmx280.begin())
  {
    Serial.println("begin() failed. check your BMx280 Interface and I2C Address.");
    while (1);
  }
  bmx280.resetToDefaults();
  bmx280.writeOversamplingPressure(BMx280MI::OSRS_P_x16);
  bmx280.writeOversamplingTemperature(BMx280MI::OSRS_T_x16);


  lcd.begin();
  lcd.clear();
  lcd.backlight();


}

void loop() {
  float temperature = 0;
  float pressure = 0;
  float humidity = 60; // default humidity
  float co2 = 0;
  float tvoc = 0;

  delay(1000);

  //start a measurement
  if (!bmx280.measure())
  {
    Serial.println("could not start measurement, is a measurement already running?");
    return;
  }

  //wait for the measurement to finish
  do
  {
    delay(100);
  } while (!bmx280.hasValue());


  pressure = bmx280.getPressure();
  temperature = bmx280.getTemperature();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(temperature,1);
  lcd.setCursor(0,1);
  lcd.print(pressure);


  // just checking in the serial monitor
  Serial.print("Temp\t");
  Serial.print(temperature);
  Serial.print("\t");
  Serial.print("Pressure\t");
  Serial.print(pressure);
  Serial.print("\t");
  Serial.println("");

  delay(200);

}
