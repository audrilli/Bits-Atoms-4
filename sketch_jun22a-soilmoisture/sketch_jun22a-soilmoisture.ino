/*  Soil Moisture Basic Example
    This sketch was written by SparkFun Electronics
    Joel Bartlett 
    August 31, 2015

    Basic skecth to print out soil moisture values to the Serial Monitor 

    Released under the MIT License(http://opensource.org/licenses/MIT)
*/

int val = 0;        //value for storing moisture value
int soilPin = A0;   //Declare a variable for the soil moisture sensor
int soilPower = 7;  //Variable for Soil moisture Power
#define ledGreen 4
#define ledRed 3

//Rather than powering the sensor through the 3.3V or 5V pins,
//we'll use a digital pin to power the sensor. This will
//prevent corrosion of the sensor as it sits in the soil.

void setup() {
  Serial.begin(9600);  // open serial over USB

  pinMode(soilPower, OUTPUT);    //Set D7 as an OUTPUT
  digitalWrite(soilPower, LOW);  //Set to LOW so no power is flowing through the sensor

  //leds
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
}

void loop() {
  Serial.print("Soil Moisture = ");
  //get soil moisture value from the function below and print it
  Serial.println(readSoil());

  if (readSoil() <= 200) {
    pinREDBlink();

    digitalWrite(ledGreen, LOW);
  } else {
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
  }

  //This 1 second timefrme is used so you can test the sensor and see it change in real-time.
  //For in-plant applications, you will want to take readings much less frequently.
  delay(1000);  //take a reading every second


  //leds

  // digitalWrite(ledGreen,HIGH);
  // digitalWrite(ledRed,HIGH);
}
//This is a function used to get the soil moisture content
int readSoil() {

  digitalWrite(soilPower, HIGH);  //turn D7 "On"
  delay(10);                      //wait 10 milliseconds
  val = analogRead(soilPin);      //Read the SIG value form sensor
  digitalWrite(soilPower, LOW);   //turn D7 "Off"
  return val;                     //send current moisture value
}

int pinREDBlink() {

  for (int i = 0; i < 10; i++) {
    digitalWrite(ledRed, HIGH);
    delay(100);
    digitalWrite(ledRed, LOW);
  }
}