// Simple sketch to access the internal hall effect detector on the esp32.
// values can be quite low. 
// Brian Degger / @sctv  

int val = 0;

void setup() {
  Serial.begin(115200);
}

// put your main code here, to run repeatedly
void loop() {
  // read hall effect sensor value
  val = hallRead();                                                                                                                                                                                                                                                                                                                                                                                                                
  Serial.print(val);
  Serial.print("  ");
  // print the results to the serial monitor
  if(val < -10) Serial.println("There's magnet");
  else Serial.println("There's no magnet");
  delay(200);
}