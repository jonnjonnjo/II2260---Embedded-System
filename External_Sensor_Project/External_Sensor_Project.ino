#include "DHT.h"

#define dhtpin 23
DHT dht(dhtpin, DHT11);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  double humidity = dht.readHumidity(); 
  double temperature = dht.readTemperature(); // celius

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("°C Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  delay(1000); // delay for a more accurate reading
}
