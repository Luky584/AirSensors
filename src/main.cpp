#include "Adafruit_CCS811.h"

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_CCS811 ccs;

#define SEALEVELPRESSURE_HPA (1007)
Adafruit_BME280 bme; // I2C BME280 sensor

void setup() {
  Serial.begin(9600);

  Serial.println("CCS811 test");
  if(!ccs.begin()){+
    Serial.println("Could not find a valid CCS811 sensor, check wiring!");
    // Force user to reboot device, show LED error effect
  }

  Serial.println(F("BME280 test"));
  if (! bme.begin(0x76, &Wire)) {
      Serial.println("Could not find a valid BME280 sensor, check wiring!");
      // Force user to reboot device, show LED error effect
  }

}

void loop() {
  if(ccs.available()){
    if(!ccs.readData()){
      Serial.print("CO2: ");
      Serial.print(ccs.geteCO2());
      Serial.print("ppm, TVOC: ");
      Serial.println(ccs.getTVOC());
    }
    else{
      Serial.println("ERROR reading CCS data!");
      // Force user to reboot device, show LED error effect
    }
  }

  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");

  Serial.print("Pressure = ");

  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.println();

  delay(1000);
}