#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display.
// The LCD address might located differently for different ESP

void setup() {
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  
  // Print a message on both lines of the LCD.
  lcd.setCursor(2,0);   //Set cursor to character 2 on line 0
  lcd.print("II2260");

  lcd.setCursor(2,1);   //Move cursor to character 2 on line 1
  lcd.print("18221079");
}

void loop() {
  lcd.print("II2260       "); 
  lcd.print("18221079     ");
}