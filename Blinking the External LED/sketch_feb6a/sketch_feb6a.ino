/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-led-blink
 */
#define BUTTON_PIN 23
int buttonState;


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin GIOP18 as an output.
  pinMode(18, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

// the loop function runs over and over again forever
void loop() {
  
  buttonState = digitalRead(BUTTON_PIN);;
  if(buttonState == 0)
  {
    digitalWrite(18,HIGH);
  }else digitalWrite(18,LOW);


}