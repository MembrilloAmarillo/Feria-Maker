#include "DHT.h"

#define DHTTYPE DHT11

/*
Connect pin 1 (on the left) of the sensor to +5V
NOTE: If using a board with 3.3V logic like an Arduino Duo connect
pin 1 to the 3.3V instead of 5V.

Connect pin 2 of the sensor to whatever your DHTPIN is
Connect pin 4 (on the right) of the sensor to GROUND
Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
*/

const int DHTPIN = 5; //What digital pin we're connected to

DHT dht(DHTPin, DHTTYPE);

void setup(){
  Serial.begin(9600);
  Serial.println("DHT 11 test!");
  // pinMode(DHTPIN, INPUT); se supone que no hace falta

  dht.begin();
}

void loop(){
  delay(2000);

  //Reading humidity-temperature takes about 2500 ms
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if(isnan(h) || isnan(t)){
    Serial.println("Failed to read from DHT sensor...");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
}
