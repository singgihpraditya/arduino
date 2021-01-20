/*
    Bluetooh Basic: LED ON OFF - Avishkar
    Coder - Mayoogh Girish
    Website - http://bit.do/Avishkar
    Download the App :
    This program lets you to control a LED on pin 13 of arduino using a bluetooth module
*/
int bluetoothValue = 0;                //Variable for storing Incoming_value
void setup()
{
  Serial.begin(9600);         //Sets the data rate in bits per second (baud) for serial data transmission
}
void loop()
{
  if (Serial.available() > 0)
  {
    bluetoothValue = Serial.read();      //Read the incoming data and store it into variable Incoming_value
 Serial.println(bluetoothValue);   //Print Value of Incoming_value in Serial monitor

  }

}
