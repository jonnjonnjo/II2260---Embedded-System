/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials  /esp32-led-blink
 */

 /*

  only rightside GPIO that's functional ( GPIO 23, GPIO22, etc...) except GP018
  on left, only GPIO32, GPIO25, GPIO26, GPIO14, GPIO12, GPIO13
 */ 

// the setup function runs once when you press reset or power the board

#define input_red 21
#define input_yellow 19
#define input_green 118

int red= 0, yellow = 0, green = 0;

void setup() {
  // initialize digital pin GIOP18 as an output.
  pinMode(23, OUTPUT);    //yellow
  digitalWrite(23,HIGH);
  pinMode(22, OUTPUT);    // green
  digitalWrite(22,HIGH);
  pinMode(1, OUTPUT);     // red
  digitalWrite(1,HIGH);

  pinMode(input_red,INPUT_PULLUP);
  pinMode(input_yellow,INPUT_PULLUP);
  pinMode(input_green,INPUT_PULLUP);
  
}

// the loop function runs over and over again forever
void loop() {
  
  /*
    0 is previous state
    1 is current state
  

  int cur_red = digitalRead(input_red);
  cur_red = !cur_red;

  if(cur_red != red)
  {
      if(cur_red == 1)
      {
        digitalWrite(1,HIGH);
      }else
      {
        digitalWrite(1,LOW);
      }

      red = cur_red;
  }

  int cur_green = digitalRead(input_green);
  cur_green = !cur_green;

  if(cur_green != green)
  {
      if(cur_green == 1)
      {
        digitalWrite(22,HIGH);
      }else
      {
        digitalWrite(22,LOW);
      }

      green = cur_green;
  }

  int cur_yellow = digitalRead(input_yellow);
  cur_yellow = !cur_yellow;

  if(cur_yellow != yellow)
  {
      if(cur_yellow == 1)
      {
        digitalWrite(23,HIGH);
      }else
      {
        digitalWrite(23,LOW);
      }

      yellow = cur_yellow;
  }

  */





}