#include<SoftwareSerial.h>



// a maximum of eight servo objects can be created

int pos = 0;    // variable to store the servo position
int bttx = 9;  //tx of bluetooth module is connected to pin 9 of arduino
int btrx = 10;  //rx of bluetooth module is connected to pin 10 of arduino

int in1 = 4; //Declaring where our module is wired
int in2 = 3;
int ConA = 5;// Don't forget this is a PWM DI/DO
int speed1;

  int direction = 1;
SoftwareSerial bluetooth(bttx, btrx);

void setup()
{
  Serial.begin(9600);
  bluetooth.begin(9600);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(ConA, OUTPUT);

}

void loop()
{
  long currentMillis = millis();
  if (bluetooth.available() > 0) //if bluetooth module is transmitting data
  {
    int bluetoothTxValue = bluetooth.read(); // store the data in pos variable
    if (bluetoothTxValue > 90 && bluetoothTxValue <= 180) {
      float btFloatTxValue = (float)bluetoothTxValue;
      Serial.println("----------------");
      Serial.println(btFloatTxValue);
      int motor1Speed = 0;
      if (btFloatTxValue > 135) {
              motor1Speed = (((btFloatTxValue - 90) / 90) * 255);
        if (direction == 0) {
          digitalWrite(in1, LOW); //Switch between this HIGH and LOW to change direction
          digitalWrite(in2, HIGH);
      Serial.println("switch direction 1");
          delay(100);
          direction = 1;

        }
      }
      else {
               motor1Speed = (((btFloatTxValue - 90) / 45) * 255);
        if (direction == 1) {
          digitalWrite(in1, HIGH); //Switch between this HIGH and LOW to change direction
          digitalWrite(in2, LOW);
      Serial.println("switch direction 0");
          delay(100);
          direction = 0;

        }

      }
       Serial.println(motor1Speed);


      Serial.println("----------------");

       analogWrite(ConA, motor1Speed);
    }
  }
}
