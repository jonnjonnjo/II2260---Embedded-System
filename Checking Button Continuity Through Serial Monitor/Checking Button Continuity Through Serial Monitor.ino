#define button 23
int i =0;

int lastState = LOW;  // the previous state from the input pin
int currentState; 

void setup() {
  // put your setup code here, to run once:
  pinMode(button,INPUT_PULLUP);
    Serial.begin(9600);
}

void loop() {
  // put your main code here, to button repeatedly:
  currentState = digitalRead(button);

  if (lastState == HIGH && currentState == LOW)
  {
    Serial.print("The button is pressed   ");
  }
  else if (lastState == LOW && currentState == HIGH)
  {
    Serial.print("The button is released  ");
  }
    

  // save the the last state
  lastState = currentState;
      Serial.println(i);
  i++;
}
