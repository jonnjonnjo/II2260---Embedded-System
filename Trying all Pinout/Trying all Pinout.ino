#define pin 13
/*
  List pinout that can be used to write ( right )
  23
  22
  1
  3
  21
  19 
  18
  5
  17
  16
  4
  2 ( you also will automatically light up the blue internal LED if you write on this pin)
  15 

  basically, we can use all right pin for write


  left : 
  32
  33
  25
  26
  27
  14
  13

*/

void setup() {
  // put your setup code here, to run once:

  pinMode(pin,OUTPUT);
  digitalWrite(pin,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

}
