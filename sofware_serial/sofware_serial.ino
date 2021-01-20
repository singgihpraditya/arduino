#include<SoftwareSerial.h>
#include<Servo.h>
Servo x;
int bttx = 9;  //tx of bluetooth module is connected to pin 9 of arduino
int btrx = 10;  //rx of bluetooth module is connected to pin 10 of arduino
SoftwareSerial bluetooth(bttx, btrx);
int post = 1;
void setup()
{
   x.attach(4);          // servo is connected to pin 11 of arduino
  Serial.begin(9600);
  bluetooth.begin(9600);
  pinMode(4, OUTPUT);
}
void loop()
{
  if (bluetooth.available() > 0) //if bluetooth module is transmitting data
  {
    int pos = bluetooth.read(); // store the data in pos variable
    Serial.println(pos);
    if (post == 1) {
      digitalWrite(4, LOW);
      post = 45;
    }
    else {
      digitalWrite(4, HIGH);
      post = 90;
    }

        x.write(post);             //move servo head to the given position
  }
  
}
