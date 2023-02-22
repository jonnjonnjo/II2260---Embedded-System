// set pin numbers
const int touchPin = 4; 
// change with your threshold value
const int threshold = 20;
// variable for storing the touch pin value 
int touchValue;
int timetouched = 0;
int touched = 0;

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display.
// The LCD address might located differently for different ESP

void show();
void initialState();

void setup(){
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  
  // Print a message on both lines of the LCD.
  initialState();
}

void loop(){
  // read the state of the pushbutton value:
  touchValue = touchRead(touchPin);
  // check if the touchValue is below the threshold
  if(touchValue < threshold){
  touched = 1;
  timetouched++;
  }
  else{
  timetouched = 0;
  touched = 0;
  }

  if(touched)show();
  else initialState();
  delay(500);
}

void show()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Touched for : ");
  int blankSpace = log(timetouched)/log(10);
  lcd.setCursor(0,1);
  lcd.print(timetouched);
  lcd.setCursor(blankSpace+2,1);
  lcd.print("Seconds");
}

void initialState()
{
  lcd.clear();
  lcd.setCursor(0,0);   //Move cursor to character 2 on line 1
  lcd.print("Please touch");
  lcd.setCursor(0,1);
  lcd.print("the Pin");
}