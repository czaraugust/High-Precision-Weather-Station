/***************************************************************************


*******************PINO D1 E D2 DO NOCEMCU**************************


 ***************************************************************************/


/************************
       BIBLIOTECAS
************************/


#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <BH1750.h>


/************************
       DEFINIÇÕES
************************/


#define Hall sensor 16  //Definição do Pino do anemômetro
#define SEALEVELPRESSURE_HPA (1013.25) //Presssão ao nível do mar. Usado para o cálculo de Altitude


/********************************************
       INICIALIZAÇÃO DO SENSORES
*********************************************/
Adafruit_BME280 bme; // I2C
BH1750 lightMeter;

unsigned long delayTime;

/********************************************
       DEFINIÇÃO DE CONSTANTES DO ANEMÔMETRO
*********************************************/

const int anemoPin = 12;
const float pi = 3.14159265;           // Numero pi
int period = 5000;               // Tempo de medida(miliseconds)
int delaytime = 5000;             // Time between samples (miliseconds)
int radius = 147;      // Raio do anemometro(mm)
long delayWhile = 0;
//  Variable definitions
unsigned int Sample = 0;   // Sample number
unsigned int counter = 0; // magnet counter for sensor
unsigned int RPM = 0;          // Revolutions per minute
float speedwind = 0;         // Wind speed (m/s)
float windspeed = 0;           // Wind speed (km/h)
long readTime = 0;













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
