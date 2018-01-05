/***************************************************************************


*******************PINO D1 E D2 DO NOCEMCU**************************


 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <BH1750.h>

BH1750 lightMeter;


#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C


unsigned long delayTime;
void printValues();
void setup() {
    Serial.begin(9600);
    Serial.println(F("BME280 test"));

    Wire.begin();
    lightMeter.begin();
    Serial.println(F("BH1750 Test"));


    bool status;

    // default settings
    // (you can also pass in a Wire library object like &Wire2)
    status = bme.begin();
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }

    Serial.println("-- Default Test --");
    delayTime = 5000;

    Serial.println();
}


void loop() {
    printValues();
    delay(delayTime);
}


void printValues() {


  uint16_t lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");



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
}
