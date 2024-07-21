#include <Arduino.h>
#line 1 "D:\\Documenti\\Github\\ArduinoVDB\\Servo\\Servo.ino"
#include <Servo.h>
Servo servo;
int angle = 10;
#line 4 "D:\\Documenti\\Github\\ArduinoVDB\\Servo\\Servo.ino"
void setup();
#line 8 "D:\\Documenti\\Github\\ArduinoVDB\\Servo\\Servo.ino"
void loop();
#line 4 "D:\\Documenti\\Github\\ArduinoVDB\\Servo\\Servo.ino"
void setup() {
  servo.attach(2);
  servo.write(angle);
}
void loop() 
{ 
    servo.write(0);
    //servo.write(90);
    //delay(60000);
    //servo.write(0);
    //delay(120000);
}
