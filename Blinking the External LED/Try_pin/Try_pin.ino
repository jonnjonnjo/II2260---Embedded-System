#define BUTTON_PIN 21 // GIOP21 pin connected to button
int i = 0;

// Variables will change:
int lastState = HIGH; // the previous state from the input pin
int currentState;     // the current reading from the input pin

void setup() {
  Serial.begin(9600);
  // initialize the pushbutton pin as an pull-up input
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // read the state of the switch/button:
  currentState = digitalRead(BUTTON_PIN);

  if(lastState == LOW && currentState == HIGH)
  {  
    i++;
    Serial.println(i);
  }

  
  // save the last state
  lastState = currentState;
}