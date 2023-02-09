#define led 23
#define button 13


/*

  list of pinout that can be used as a reader
  
  right :
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
  2     ( not responsive. Always generate 1)
  15

  The left one is the reverse of the right one. 
  

  left : 
  36 
  39
  34
  35
  32  ( Normal )
  33  ( Normal )
  25  ( Normal )
  26  ( normal )
  27  ( normal )
  14  ( normal)
  12  ( normal )
  13  ( normal )

  what I mean by normal is that they work the same way as the right side.
  Beside the normal one, the natural state of the LED will be on ( the normal one should be off).
  And if we click the button, It will make the LED slightly lighter.


*/

void setup()
{
  pinMode(led,OUTPUT);
  pinMode(button,INPUT_PULLUP);
}

void loop()
{
  int state = digitalRead(button);
  if(!state)
  {
    digitalWrite(led,HIGH);
  }else digitalWrite(led,LOW);

}