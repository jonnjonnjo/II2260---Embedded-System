#include <LiquidCrystal_I2C.h>
#define backwardButton  23
#define stoppedButton 1
#define forwardButton 3
int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14; 
// Setting PWM properties
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 200;

int backwardStateBefore = 0, stoppedStateBefore = 0, forwardStateBefore = 0;
int backwardStateNow, stoppedStateNow, forwardStateNow;

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display.
// The LCD address might located differently for different ESP

void setup() {
  lcd.begin();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  
  // Print a message on both lines of the LCD.
  Serial.begin(9600);
  lcd.setCursor(0,0);   //Move cursor to character 2 on line 1
  lcd.print("Condition : ");
  pinMode(backwardButton,INPUT_PULLUP);
  pinMode(stoppedButton,INPUT_PULLUP);
  pinMode(stoppedButton,INPUT_PULLUP);

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  // configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel);
  
}

void loop() {

  
  // input the button condition now
  backwardStateNow = !digitalRead(backwardButton);
  stoppedStateNow = !digitalRead(stoppedButton);
  forwardStateNow =  !digitalRead(forwardButton);


  if(backwardStateNow == backwardStateBefore && stoppedStateBefore == stoppedStateNow && forwardStateBefore == forwardStateNow)
  {
      return;
  }


  // test 3 case
  // in case it wants to go backward
  if(backwardStateNow == 1 && stoppedStateNow == 0 && forwardStateNow ==0)
  {
  lcd.clear();
   lcd.setCursor(0,0);  
  lcd.print("Condition : ");
  lcd.setCursor(0,1);
      lcd.print("Moving Backwards");
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW); 
  }

  // in case it wants to go forward

  if(backwardStateNow == 0 && stoppedStateNow == 0 && forwardStateNow == 1)
  {
  lcd.clear();
   lcd.setCursor(0,0);  
  lcd.print("Condition : ");
  lcd.setCursor(0,1);
      lcd.print("Moving Forwards");
      digitalWrite(motor1Pin1,LOW); 
      digitalWrite(motor1Pin2,HIGH);
  }


  // in case it wants to go stop
  if(backwardStateNow == 0 && stoppedStateNow == 1 && forwardStateNow == 0)
  {
  lcd.clear();
   lcd.setCursor(0,0);  
  lcd.print("Condition : ");
  lcd.setCursor(0,1);
      lcd.print("Stopped");
      digitalWrite(motor1Pin1,LOW);
      digitalWrite(motor1Pin2,LOW);
  }


  // set the previous state
  backwardStateBefore = backwardStateNow;
  stoppedStateBefore = stoppedStateNow;
  forwardStateBefore = forwardStateNow;


  delay(200); // some delay 


}