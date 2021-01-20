#include<SoftwareSerial.h>
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// a maximum of eight servo objects can be created

int pos = 0;    // variable to store the servo position
int bttx = 9;  //tx of bluetooth module is connected to pin 9 of arduino
int btrx = 10;  //rx of bluetooth module is connected to pin 10 of arduino
SoftwareSerial bluetooth(bttx, btrx);


void setup()
{
  Serial.begin(9600);
  bluetooth.begin(9600);
  myservo.attach(4);  // attaches the servo on pin 9 to the servo object
}

void loop()
{
  if (bluetooth.available() > 0) //if bluetooth module is transmitting data
  {
    int inblue = bluetooth.read(); // store the data in pos variable
    Serial.println(inblue);
     myservo.write(pos);    
  }
 
}
