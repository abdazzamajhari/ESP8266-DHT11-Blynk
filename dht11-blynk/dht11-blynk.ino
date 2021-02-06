#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include "DHT.h"

char auth[] = "S6kgpOckbJWevYez5Rxrr2kKcLAw5SXj";
char ssid[] = "Azzam";
char pass[] = "azzam53a";

#define DHTPIN D1
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

void sendSensor()
{
  float hum = dht.readHumidity();
  float tem = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(hum) || isnan(tem)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, tem);
  Blynk.virtualWrite(V6, hum);
}

void setup(){
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  
  dht.begin();

  timer.setInterval(1000L, sendSensor);
}
void loop()
{ 
  Serial.println(" ====== DHT11 SENSOR ====== ");
  
  float hum = dht.readHumidity();
  float tem = dht.readTemperature();
  Serial.print(" Humidity DHT11: ");
  Serial.print(hum);
  Serial.print("% ");
  Serial.print("\n");
  Serial.print(" Temperature DHT11: ");
  Serial.print(tem);
  Serial.print("°C ");
  Serial.print(">>> ");
  Serial.print((int)round(1.8*tem+32));
  Serial.println("°F ");

  Blynk.run();
  timer.run();
  
  delay(10000); //waiting for 10 seconds
}
