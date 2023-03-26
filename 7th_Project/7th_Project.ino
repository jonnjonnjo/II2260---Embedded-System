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
int displayOnLCD = 0;

// for light sensor
int light = 0;
const int IN_D0 = 23; // digital input

BluetoothSerial SerialBT;
String message = "";
char incomingChar;
String help[] = {"Print in LCD Display","Print here","Temperature","Pressure","Light"};

bool validateParameter(String type)
{
  for(int i = 0;i <5;i++)
  {
    if(help[i] == type) return true;
  }
  return false;
}


void display(String type)
{
  if(displayOnLCD)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    if(type != "Print here") lcd.print(type);
    else
    {
      lcd.print("Printed on phone");
      return;
    }
    lcd.setCursor(0, 1);

    if(type == "Temperature")
    {
      lcd.print(temperature);
      lcd.setCursor(5,1);
      lcd.print("C");
    }else if(type == "Pressure")
    {
      lcd.print(pressure);
      lcd.setCursor(8,1);
      lcd.print("C");
    }else if(type == "Light")
    {
      lcd.print(light ? "There's Light" : "No Light"); 
    }
  }else
  {
    // print to the 
    for(int i = 0;i <type.length();i++) SerialBT.write(type[i]);
    SerialBT.write(' ');
    SerialBT.write(':');
    SerialBT.write(' ');
    String temp;
    if(type == "Temperature")
    {
      temp = String(temperature);
    }else if(type == "Pressure")
    {
      temp = String(pressure);
    }else if(type == "Light")
    {
      temp = light >0 ? "There's light" :"There's no light";
    }


    for(int i = 0;i < temp.length();i++) SerialBT.write(temp[i]);
    SerialBT.write('\n');
  }
}

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
  bmx280.resetToDefaults();
  bmx280.writeOversamplingPressure(BMx280MI::OSRS_P_x16);
  bmx280.writeOversamplingTemperature(BMx280MI::OSRS_T_x16);

  // for light sensor
  pinMode(IN_D0, INPUT);

}

void loop() {

  
  // for bmp
  temperature = 0;
  pressure = 0;

  // light sensor
  light = digitalRead(IN_D0);

  //start a measurement
  if (!bmx280.measure())
  {
    return;
  }
  do
  {
    delay(1);
  } while (!bmx280.hasValue());

  //wait for the measurement to finish


  pressure = bmx280.getPressure();
  temperature = bmx280.getTemperature();

  

  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    incomingChar = SerialBT.read();
    if(incomingChar != '\n')
    {
      message += incomingChar;
    }else
    {
      message = "";
    }
    Serial.write(incomingChar);  
  }


    if(message == "Print in LCD Display")
    {
      displayOnLCD = 1;
    }else if(message == "Print here")
    {
      displayOnLCD = 1;
      display("Print here");
      displayOnLCD = 0;
    }else if(validateParameter(message))
    {
      display(message);
    }
    
  delay(200);

  
}