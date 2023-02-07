#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define BUTTON_PIN 23
long clicks = 999999999999999;


LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display.
// The LCD address might located differently for different ESP


/*
  reference link : https://arduinointro.com/projects/create-custom-characters-for-the-i2c-lcd-easily
  custom character generator : https://omerk.github.io/lcdchargen/

*/

byte bef[] = {
	0b11111,
	0b10001,
	0b10001,
	0b10001,
	0b10001,
	0b10001,
	0b10001,
	0b11111
};

byte af[] = {
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111
};

void setup() {
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  lcd.createChar(1, bef);
  lcd.createChar(2, af);
  
  // Print a message on both lines of the LCD.

  lcd.setCursor(0,0);   //Move cursor to character 2 on line 1
  lcd.print("18221079");

  lcd.setCursor(0,1);
  lcd.write(byte(1));
  
}

void loop() {

  delay(2000);
  lcd.write(byte(2));

}