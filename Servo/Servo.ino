#include <Servo.h>
Servo servo;
int angle = 10;
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