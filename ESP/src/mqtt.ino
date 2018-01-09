// Pin definitions
# define Hall sensor 16         //  Pino digital anemometro

// Anemometro
// Constants definitions
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

// Pluviometro
// Constants definitions
const int pluvPin = 14;              //The reed switch outputs to digital pin 9
//  Variable definitions
int val = 0;                    //Current value of reed switch
int old_val = 0;                //Old value of reed switch
int reedcount = 0;              //This is the variable that hold the count of switching

long printTime = 0;
int valorAnalog = 0;

void setup()
{
  // Set the pins
  // Anemometro
  pinMode(anemoPin, INPUT_PULLUP);
  // Pluviometro
  pinMode(pluvPin, INPUT_PULLUP);

  printTime = millis();
  readTime = millis();

  // Start serial
  Serial.begin(9600);       // sets the serial port to 9600 baud
  }

void loop()
{
  //Sample++;
  //Serial.print("Sample: ");
  //Serial.println(Sample);

  if(millis() > printTime+delaytime){
    Serial.print("Analog: ");
    valorAnalog = analogRead(0);
    Serial.println(valorAnalog);

    printTime = millis();
  }

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
    Serial.println(counter);
    counter = 0;
    attachInterrupt(anemoPin, addcount, RISING);

    readTime = millis() + period;
  }

  // Pluviometro
  val = digitalRead(pluvPin);      //Read the status of the Reed swtich
  //Serial.println(val);
  if ((val == LOW) && (old_val == HIGH)){    //Check to see if the status has changed
    delay(10);                   // Delay put in to deal with any "bouncing" in the switch.
    reedcount = reedcount + 1;   //Add 1 to the count of bucket tips
    old_val = val;              //Make the old value equal to the current value
    Serial.print("Medida de chuva (contagem): ");
    Serial.print(reedcount);//*0.2794);
    Serial.println(" pulso");
    Serial.print("Medida de chuva (calculado): ");
    Serial.print(reedcount*0.25);
    Serial.println(" mm");
    } else {
      old_val = val;              //If the status hasn't changed then do nothing
    }

  //delay(delaytime);                        //delay between prints
}

/*
// Measure wind speed
void windvelocity(){
  speedwind = 0;
  windspeed = 0;

  counter = 0;
  attachInterrupt(anemoPin, addcount, RISING);
  unsigned long millis();
  long startTime = millis();
  wdt_disable();
  while(millis() < startTime + period) {
  }
  wdt_enable(WDTO_4S);
}

void RPMcalc(){
  RPM=((counter)*60)/(period/1000);  // Calculate revolutions per minute (RPM)
}

void WindSpeed(){
  windspeed = ((4 * pi * radius * RPM)/60) / 1000;  // Calculate wind speed on m/s
}

void SpeedWind(){
  speedwind = (((4 * pi * radius * RPM)/60) / 1000)*3.6;  // Calculate wind speed on km/h
}
*/

void addcount(){
  counter++;
}
