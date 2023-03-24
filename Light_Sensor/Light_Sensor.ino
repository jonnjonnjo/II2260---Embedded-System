#include <Wire.h>


const int IN_A0 = 36; // analog input
const int IN_D0 = 23; // digital input
int value_A0;
bool value_D0;

void setup() {
  pinMode (IN_A0, INPUT);

  Serial.begin(115200);
  pinMode (IN_D0, INPUT);

}


void loop() {

  value_A0 = analogRead(IN_A0); // reads the analog input from the IR distance sensor
  value_D0 = digitalRead(IN_D0);// reads the digital input from the IR distance sensor
  
  Serial.print("A0 :");
  Serial.print(value_A0); // prints analog value on the LCD module

  Serial.print("  D0:");
  Serial.println(value_D0); // prints digital value on the LCD module
  
  delay(1000);
}