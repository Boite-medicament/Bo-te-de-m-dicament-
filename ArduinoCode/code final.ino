/*
 Controlling a servo position 
Connect :
- brown cable to GND
- Red Cable to V_in (5V from USB)
- Orange to A0
*/

/* 
 Ultrasonic sensor
Connect :
Ucc to 5V 
Trig to D3
Echo to D2
Gnd to Gnd
*/

/*
 LED Screen
Connect :
VCC to Vcc_mcu (3.3V)
GND to GND
SCL to UCA pin A5 (or the SCL pin for your arduino)
SDA to UCA pin A4 (or the SDA pin for your arduino)
*/


// Include libraries:
#include "lcdgfx.h"
#include <Servo.h>
                   
Servo myservo;                            // create servo object to control a servo
DisplaySSD1306_128x64_I2C display(-1);

// define constants:
#define echoPin 2                         // the compiler will replace any mention of echoPin with the value 4 at compile time
#define trigPin 3                         // the compiler will replace any mention of trigPin with the value 5 at compile time

// Define variables:
int potpin = 0;                           // analog pin used to connect the potentiometer
int val;                                  // variable to read the value from the analog pin
long duration;                            // extended variable, time taken by the signal of the ultrassonic sensor to be emitted then received
int distance;                             // integer (= entier), distance between the sensor and the object in front of it


void setup() {
  myservo.attach(A0);                     // attach myservo to pin A0
  pinMode (trigPin, OUTPUT);              // define trigPin as an OUTPUT
  pinMode (echoPin, INPUT);               // define echoPin as an INPUT
  Serial.begin(9600);                     // set the baud rate to 9600 Bd
  display.begin();
  display.fill(0x00);
  display.setFixedFont(ssd1306xled_font6x8);
  }


void loop() {
  digitalWrite(trigPin, LOW);             // set the trigPin at LOW ( =0V )
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);            // set the trigPin at HIGH (=5V), the sensor send a signal during 10 microseconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);             // set the trigPin back at LOW 
  duration = pulseIn(echoPin, HIGH);      // time taken by the signal of the ultrassonic sensor to be emitted then received, in microseconds 
  delay(100);
  distance = duration * 0.034 / 2;        // distance between the sensor and the object in front of it, in centimeters
  Serial.print(distance);                 // print the distance in the monitor
  val = map(val, 0, 1023, 0, 180);
  delay(200);
  
  if(distance < 10)                                                                      // if someone put his in front of the sensor 
  {
    Serial.println(" ");
    display.printFixedN (0, 16, "                         ", STYLE_BOLD, FONT_SIZE_2X); // erase the old message
    display.printFixedN (0, 32, "             ", STYLE_BOLD, FONT_SIZE_2X);
    display.printFixedN (0, 16, "Medicament Pris ", STYLE_BOLD, FONT_SIZE_2X);          // display the sentence on the screen
    myservo.write(90);                                                                  // the servomoteur rotate in a 90 degres angle then take his originale place back
    delay(200);
    myservo.write(0);
    delay(2000);
   }
  
  else                                                                                    // the screen will show if the medicine must be taken or has already been 
  {
   Serial.println(" ");
   display.printFixedN (0, 16, "                    ", STYLE_BOLD, FONT_SIZE_2X);
   display.printFixedN (0, 32, "                   ", STYLE_BOLD, FONT_SIZE_2X);
   display.printFixedN (0, 16, "   Prendre ", STYLE_BOLD, FONT_SIZE_2X);  
   display.printFixedN (0, 32, "Medicament", STYLE_BOLD, FONT_SIZE_2X);
   delay(100);
  }
}
