
/************************
      BIBLIOTECAS
************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <BH1750.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

/************************
        MQTT
************************/

const char* ssid = "EASY";
const char* password = "tv123456";
const char* mqtt_server = "192.168.0.168";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {

  /*WiFi.mode(WIFI_STA);
  WiFi.disconnect();*/
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

 /*while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }*/

  //randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}



/************************
        DEFINIÇÕES
************************/

#define SEALEVELPRESSURE_HPA (1013.25) //Presssão ao nível do mar. Usado para o cálculo de Altitude
unsigned long delayTime =  5000;
int valorAnalog = 0;
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

generalCount++;
if (generalCount >= 17280){ //24 horas
    generalCount =0;
    reedcount =0;

}
/********************************************
                  ANEMOSCÓPIO
*********************************************/
valorAnalog = analogRead(0);
//Serial.println(valorAnalog);

  if(valorAnalog >= 100 && valorAnalog < 135){
    Serial.println(" NO");
  }
  else if(valorAnalog >= 135 && valorAnalog < 155){
    Serial.println(" O");
  }
  else if(valorAnalog >= 155 && valorAnalog < 175){
    Serial.println(" SO");
  }
  else if(valorAnalog >= 175 && valorAnalog < 200){
    Serial.println(" S");
  }
  else if(valorAnalog >= 200 && valorAnalog <= 240){
    Serial.println(" SE");
  }
  else if(valorAnalog >= 240 && valorAnalog <= 300){
    Serial.println(" E");
  }
  else if(valorAnalog >= 300 && valorAnalog <= 400){
    Serial.println(" NE");
  }
  else if(valorAnalog >= 400 && valorAnalog <= 600){
    Serial.println(" N");
  }

Serial.println();

}

void addReedcount(){
  reedcount++;

}
void addcount(){
  counter++;
}
