#include "DHT.h"        // using temperature and humidity sensor

#define DHTTYPE DHT11   // type set
#define DHTPIN 22       // DHT11 pin number

#define PIN_RELAY 24    // set relay pin number

DHT dht1(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.println(F("DHT11 test"));
  
  pinMode(PIN_RELAY, OUTPUT);   // set pin mode
  digitalWrite(PIN_RELAY, LOW); // set default relay off
  
  dht1.begin();
}

void loop() {
  
  delay(1000);      // gap between reloads

  float hum = dht1.readHumidity(); //humidity value 
  float tem = dht1.readTemperature(); // temperature value

  // checking for failures
  if(isnan(hum) || isnan(tem)) {
    Serial.println(F("Failed to read values"));
    return;
  }

  if(hum <= 50) {
    digitalWrite(PIN_RELAY, HIGH);
  } else {
    digitalWrite(PIN_RELAY, LOW);
  }

  float heatIndex = dht1.computeHeatIndex(tem, hum, false);

  Serial.print(F("Humidity: "));
  Serial.print(hum);
  Serial.print(F("% Temperature: "));
  Serial.print(tem);
  Serial.print(" Heat index: ");
  Serial.print(heatIndex);
  Serial.print(F("\n"));
}
