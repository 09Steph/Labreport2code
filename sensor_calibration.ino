#define L1Pin 36 //defines all the analoge pins
#define L2Pin 39 
#define M1Pin 34
#define M2Pin 35
#define R1Pin 32
#define R2Pin 33
#include <Wire.h>

void setup() {   //setups up function
 Serial.begin(9600);
 Wire.begin();
}

void loop() {
//Serial.println("running"); //print statement to enseur loop funvtion rus
Serial.println(analogRead(R2Pin)); //code to read and print the value from the pin and subsequent sensor
//Serial.println("working"); //print statement to ensure code does execute

}
// white = 400 - 500
//black = 4095