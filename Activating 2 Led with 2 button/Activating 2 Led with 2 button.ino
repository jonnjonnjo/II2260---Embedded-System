#define led_yellow 18
#define led_red  1
#define led_green 23
#define button_green 3
#define button_red 5
#define button_yellow 19


 int state_green = 0;
 int state_yellow = 0;
 int state_red = 0;

int cy = 0, cr = 0, cg = 0;


#include <LiquidCrystal_I2C.h>

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

void setup()
{
  pinMode(led_yellow,OUTPUT);
  pinMode(led_green,OUTPUT);
  pinMode(led_red,OUTPUT);

  pinMode(button_green,INPUT_PULLUP);
  pinMode(button_yellow,INPUT_PULLUP);
  pinMode(button_red,INPUT_PULLUP);

  // try
 // digitalWrite(led_yellow,HIGH);
  //digitalWrite(led_green,HIGH);
  //digitalWrite(led_red,HIGH);


    // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight(); 




}

void loop()
{
  
  int green = digitalRead(button_green);

   if(green != state_green)
   {
    if(green == 0)
    {
      digitalWrite(led_green,HIGH);
      cg++;
    }
    else digitalWrite(led_green,LOW);
    
     state_green = green;
   }

  int red = digitalRead(button_red);

   if(red != state_red)
   {
    if(red == 0)
    {
      digitalWrite(led_red,HIGH);
      cr++;
    } 
    else digitalWrite(led_red,LOW);

     state_red = red;
   }

  int yellow = digitalRead(button_yellow);

   if(yellow != state_yellow)
   {
    if(yellow == 0)
    {
       digitalWrite(led_yellow,HIGH);;
        cy++;
    }
    else digitalWrite(led_yellow,LOW);

     state_yellow = yellow;
   }


  lcd.setCursor(0, 0);
  lcd.print("GREEN : ");
  lcd.setCursor(8,0);
  lcd.print(cg);

  lcd.setCursor(0,1);
  lcd.print("RED : ");
  lcd.setCursor(6,1);
  lcd.print(cr);


  lcd.setCursor(9,1);
  lcd.print("YLW:");
  lcd.setCursor(13, 1);
  lcd.print(cy);







}