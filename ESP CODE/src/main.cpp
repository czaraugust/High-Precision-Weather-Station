
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
  const char* mainTopic = "weatherstation";

  WiFiClient espClient;
  PubSubClient client(espClient);
  int contador =0;


  void setup_wifi() {

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    int connRes = WiFi.waitForConnectResult();
    Serial.print ( "connRes: " );
    Serial.println ( connRes );
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

  void reconnect() {

    while (WiFi.status() != WL_CONNECTED){
      Serial.println("Rec wifi");
      setup_wifi();
    }
    // Loop until we're reconnected
    while (!client.connected()) {
      Serial.print("Attempting MQTT connection...");
      // Create a random client ID
      String clientId = "ESP8266Client-";
      //clientId += String(WiFi.macAddress(), HEX);
      // Attempt to connect
      if (client.connect(clientId.c_str())) {
        Serial.println("connected");
        // Once connected, publish an announcement...
        client.publish(mainTopic, "OLA!");
        // ... and resubscribe
        client.subscribe("devicesub");
      } else {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        // Wait 5 seconds before retrying
        delay(5000);
      }
    }
  }

  /************************
          DEFINIÇÕES
  ************************/

  #define SEALEVELPRESSURE_HPA (1013.25) //Presssão ao nível do mar. Usado para o cálculo de Altitude
  unsigned long delayTime =    60000;

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
  //int delaytime = 5000;             // Time between samples (miliseconds)
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
  void callback(char* topic, byte* payload, unsigned int length) {
    // Serial.print("Message arrived [");
    // Serial.print(topic);
    // Serial.print("] ");
    // for (int i = 0; i < length; i++) {
    //   Serial.print((char)payload[i]);
    // }
    // Serial.println();
    //
    // // Switch on the LED if an 1 was received as first character
    // if ((char)payload[0] == '1') {
    //   digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    //   // but actually the LED is on; this is because
    //   // it is acive low on the ESP-01)
    // } else {
    //   digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
    //}

  }



  void setup() {
  //      SETUP DOS PINOS
    // Anemometro
    pinMode(anemoPin, INPUT_PULLUP);
    // Pluviometro
    pinMode(pluvPin, INPUT_PULLUP);

    printTime = millis();
    readTime = millis();

    //    INICIALIZAÇÃO DOS SENSORES
    Serial.begin(115200);
    Wire.begin();
    lightMeter.begin();
    bme.begin();
    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
    Serial.println();
    delay(1000);
  }

  /********************************************
                    LOOP
  *********************************************/

  void loop() {
    contador ++;

    if (!client.connected()) {
    reconnect();
  }
    client.loop();
    printValues();
    delay(delayTime);

  }


  void printValues() {

    String message = "@";
    message += contador;
    message += "|";

    /********************************************
                      LUXÍMETRO
    *********************************************/

    uint16_t lux = lightMeter.readLightLevel();
    Serial.print("Light: ");
    Serial.print(lux);
    Serial.println(" lx");
    message += lux;
    message += "|";
    /********************************************
                      TERMÔMETRO
    *********************************************/

    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" ºC");
    message += bme.readTemperature();
    message += "|";

    /********************************************
                      BARÔMETRO
    *********************************************/

    Serial.print("Pressure = ");
    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");
    message += (bme.readPressure() / 100.0F);
    message += "|";
    /********************************************
                      ALTÍMETRO
    *********************************************/

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");
    message += bme.readAltitude(SEALEVELPRESSURE_HPA) ;
    message += "|";
    /********************************************
                      HIGRÔMETRO
    *********************************************/

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" % ");
    message += bme.readHumidity();
    message += "|";


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
      message += speedwind;
      message += "|";
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
  message += (reedcount*0.25);
  message += "|";
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

  if(valorAnalog < 140){
    Serial.println(" NO");
    message += "NO";
    message += "|";
  }
  else if(valorAnalog >= 140 && valorAnalog < 170){
    Serial.println(" O");
    message += "O";
    message += "|";
  }
  else if(valorAnalog >= 170 && valorAnalog < 190){
    Serial.println(" SO");
    message += "SO";
    message += "|";
  }
  else if(valorAnalog >= 190 && valorAnalog < 220){
    Serial.println(" S");
    message += "S";
    message += "|";
  }
  else if(valorAnalog >= 220 && valorAnalog <= 285){
    Serial.println(" SE");
    message += "SE";
    message += "|";
  }
  else if(valorAnalog >= 285 && valorAnalog <= 390){
    Serial.println(" E");
    message += "E";
    message += "|";
  }
  else if(valorAnalog >= 390 && valorAnalog <= 550){
    Serial.println(" NE");
    message += "NE";
    message += "|";
  }
  else if(valorAnalog >= 600){
    Serial.println(" N");
    message += "N";
    message += "|";
  }
  client.publish(mainTopic, message.c_str());
  Serial.println(message.c_str());

  }

  void addReedcount(){
    reedcount++;

  }
  void addcount(){
    counter++;
  }
