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
unsigned long delayTime =  5000;

/********************************************
            DECLARAÇÃO DO SENSORES I2C
*********************************************/
Adafruit_BME280 bme; // I2C
BH1750 lightMeter;



/********************************************
                  ANEMÔMETRO
*********************************************/

//          DEFINIÇÃO DE CONSTANTES
const int anemoPin = 12;
const float pi = 3.14159265;           // Numero pi
int period = 5000;               // Tempo de medida(miliseconds)
int delaytime = 5000;             // Time between samples (miliseconds)
int radius = 147;      // Raio do anemometro(mm)
long delayWhile = 0;

//          DEFINIÇÃO DE VARIÁVEIS
unsigned int Sample = 0;   // Sample number
unsigned int counter = 0; // magnet counter for sensor
unsigned int RPM = 0;          // Revolutions per minute
float speedwind = 0;         // Wind speed (m/s)
float windspeed = 0;           // Wind speed (km/h)
long readTime = 0;


/********************************************
                  PLUVIÔMETRO
*********************************************/

//          DEFINIÇÃO DE CONSTANTES
const int pluvPin = 14;              //The reed switch outputs to digital pin 9

//          DEFINIÇÃO DE VARIÁVEIS
int val = 0;                    //Current value of reed switch
int old_val = 0;                //Old value of reed switch
int reedcount = 0;              //This is the variable that hold the count of switching
long printTime = 0;
int valorAnalog = 0;
int generalCount =0;


void printValues();
void addcount();
void addReedcount();
/********************************************
                  SETUP
*********************************************/
void setup() {
//      SETUP DOS PINOS
  // Anemometro
  pinMode(anemoPin, INPUT_PULLUP);
  // Pluviometro
  pinMode(pluvPin, INPUT_PULLUP);

  printTime = millis();
  readTime = millis();

  //    INICIALIZAÇÃO DOS SENSORES
  Serial.begin(9600);
  Wire.begin();
  lightMeter.begin();
  bme.begin();

  Serial.println();
}

/********************************************
                  LOOP
*********************************************/

void loop() {
  printValues();
  delay(delayTime);



}


void printValues() {

  /********************************************
                    LUXÍMETRO
  *********************************************/

  uint16_t lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");

  /********************************************
                    TERMÔMETRO
  *********************************************/

  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" ºC");

  /********************************************
                    BARÔMETRO
  *********************************************/

  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  /********************************************
                    ALTÍMETRO
  *********************************************/

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  /********************************************
                    HIGRÔMETRO
  *********************************************/

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  /********************************************
                    ANEMÔMETRO
  *********************************************/

  if(millis() > readTime){
    RPM=((counter)*60)/(period/1000);  // Calculate revolutions per minute (RPM)
    windspeed = ((4 * pi * radius * RPM)/60) / 1000;  // Calculate wind speed on m/s
    speedwind = (((4 * pi * radius * RPM)/60) / 1000)*3.6;  // Calculate wind speed on km/h

    // Anemometro
    Serial.print("Wind speed: ");
    Serial.print(windspeed);
    Serial.print(" [m/s] ");
    Serial.print(speedwind);
    Serial.print(" [km/h] ");
    Serial.println();

    speedwind = 0;
    windspeed = 0;
    //Serial.println(counter);
    counter = 0;
    attachInterrupt(anemoPin, addcount, RISING);

    readTime = millis() + period;
  }

  /********************************************
                    PLUVIÔMETRO
  *********************************************/

attachInterrupt(pluvPin,addReedcount, FALLING);
Serial.print("Accumulated rainfall in the past 24 hrs: ");
Serial.print(reedcount*0.25);
Serial.println(" mm");
Serial.println();
generalCount++;
if (generalCount >= 17280){ //24 horas
    generalCount =0;
    reedcount =0;

}


}

void addReedcount(){
  reedcount++;

}
void addcount(){
  counter++;
}
