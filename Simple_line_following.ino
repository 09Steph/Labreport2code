#define L1Pin 14 //define analogue pins to esp32 which connects to the sensors
#define L2Pin 27
#define M1Pin 26
#define M2Pin 25
#define R1Pin 35
#define R2Pin 34
#define I2C_SLAVE_ADDR 0x04
#include <Wire.h>

int leftMotor_speed = 255;  //defining variables sent to the ESP32 and Nano
int rightMotor_speed = 255;
int black_value=4095,white_value=420, distance=68; //defining the sensors values from the calibration code to variables 
int servoAngle;

void setup() { //setup code
 Serial.begin(9600);
 Wire.begin();

}

void loop() { //code below reads values from sensors and calculates weighted average
 double Left_1 = map(constrain(analogRead(L1Pin),black_value,white_value),black_value,white_value,5,0);
 double Left_2 = map(constrain(analogRead(L2Pin),black_value,white_value),black_value,white_value,5,0);
 double Mid_1 = map(constrain(analogRead(M1Pin),black_value,white_value),black_value,white_value,5,0);
 double Mid_2 = map(constrain(analogRead(M2Pin),black_value,white_value),black_value,white_value,5,0);
 double Right_1 = map(constrain(analogRead(R1Pin),black_value,white_value),black_value,white_value,5,0);
 double Right_2 = map(constrain(analogRead(R2Pin),black_value,white_value),black_value,white_value,5,0);
 double weighted_avg = ((Left_1*distance)+(Left_2*distance)+(Mid_1*distance)+(Mid_1*distance)+(Mid_2*distance)+(Right_1* distance)+(Right_2* distance))/(Left_1 + Left_2 + Mid_1 + Mid_2 + Right_1 + Right_2);

if (weighted_avg < 0) // if statements determined by the weighted average variable 
{
  servoAngle = 20; // servo angle for left 
}
else if  (weighted_avg > 0) {
  servoAngle = 150; // servo angle for right
}
else 
{
  servoAngle = 89; //servo angle for straight 
}
Transmit_to_arduino(leftMotor_speed, rightMotor_speed, servoAngle);

}
 void Transmit_to_arduino(int leftMotor_speed, int rightMotor_speed, int servoAngle) //function to send 3 values to the Nano

{
  Wire.beginTransmission(I2C_SLAVE_ADDR); // transmit to device #4
  Wire.write((byte)((leftMotor_speed & 0x0000FF00) >> 8));    // first byte of x, containing bits 16 to 9
  Wire.write((byte)(leftMotor_speed & 0x000000FF));           // second byte of x, containing the 8 LSB - bits 8 to 1
  Wire.write((byte)((rightMotor_speed & 0x0000FF00) >> 8));   // first byte of y, containing bits 16 to 9
  Wire.write((byte)(rightMotor_speed & 0x000000FF));          // second byte of y, containing the 8 LSB - bits 8 to 1
  Wire.write((byte)((servoAngle & 0x0000FF00) >> 8));    // first byte of x, containing bits 16 to 9
  Wire.write((byte)(servoAngle & 0x000000FF));
  Wire.endTransmission();   // stop transmitting
}