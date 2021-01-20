#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// a maximum of eight servo objects can be created


void setup()
{
  Serial.begin(9600);
  myservo.attach(4);  // attaches the servo on pin 9 to the servo object
}

void loop()
{

       myservo.write(1);
       delay(1000);
       myservo.write(180);
       delay(1000);


}
