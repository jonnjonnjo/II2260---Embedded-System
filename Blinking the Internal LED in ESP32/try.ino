#define LED 2

void setup() {
  // Set pin mode
  pinMode(LED,OUTPUT);
}

void loop() {
  // you can adjust your delay here. I make the LED turned on every 50 ms
  delay(50);
  digitalWrite(LED,HIGH);
  delay(50);
  digitalWrite(LED,LOW);
}
