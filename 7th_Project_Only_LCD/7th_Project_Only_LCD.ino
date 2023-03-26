// include all library
#include "DHT.h"
#include "BluetoothSerial.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

// declare some variable
#define dhtpin 23
DHT dht(dhtpin, DHT11);
String message = "";
char incomingChar;
int wantToPrint = 0;
int printInLCD = 0;
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Jon's ESP32"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  
  // setting up the dht sensor
  dht.begin();

  // setting up the lcd
  lcd.begin();
  lcd.clear();         
  lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
  double humidity = dht.readHumidity(); 
  double temperature = dht.readTemperature(); // celius

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

  if(message == "in LCD") // in case you want it to be printed in LCD
  {
    printInLCD = 1;
  }else if(message == "in Phone") // in case you want it to be printed on you phone
  {
    printInLCD = 0;
  }
  else if(wantToPrint) // in case you want to print some string
  {
    if(printInLCD)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(message);
      if(message.length() > 16)
      {
        for(int i =0;i + 15 < message.length();i++)
        {
          lcd.setCursor(i,1);
          lcd.print(message[i+15]);
        }
      }
    }else
    {
      for(int i =0;i < message.length();i++) SerialBT.write(message[i]);
    }
  }
  else if(message == "Print") // declare that you want to print something
  {
    wantToPrint = 1;
  }else if(message == "Temperature") // ask about the temperature
  {
    if(printInLCD)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Temperature : ");
      lcd.setCursor(0,1);
      lcd.print(temperature);
      lcd.setCursor(5,1);
      lcd.print(" C");
    }else
    {
      for(int i =0;i < message.length();i++) SerialBT.write(message[i]);
      SerialBT.write(' ');
      SerialBT.write(':');
      SerialBT.write(' ');

      String temp = String(temperature);

      for(int i = 0;i < temp.length();i++) SerialBT.write(temp[i]);
      SerialBT.write(' ');
      SerialBT.write('°');
      SerialBT.write('C');
    }
  }else if(message == "Humidity") // ask about the humidity
  {
    if(printInLCD)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Humidity : ");
      lcd.setCursor(0,1);
      lcd.print(humidity);
      lcd.setCursor(5,1);
      lcd.print(" °C");
    }else
    {
      for(int i =0;i < message.length();i++) SerialBT.write(message[i]);
      SerialBT.write(' ');
      SerialBT.write(':');
      SerialBT.write(' ');

      String temp = String(humidity);

      for(int i = 0;i < temp.length();i++) SerialBT.write(temp[i]);
      SerialBT.write(' ');
      SerialBT.write('%');
    }
  }

  delay(200);
}