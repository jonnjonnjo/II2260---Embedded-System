#include <LiquidCrystal_I2C.h>
#define BUTTON_PIN 23
long clicks = 999999999999999;


LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display.
// The LCD address might located differently for different ESP

void setup() {
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  
  // Print a message on both lines of the LCD.

  lcd.setCursor(0,0);   //Move cursor to character 2 on line 1
  lcd.print("18221079");
  
}

void loop() {

}