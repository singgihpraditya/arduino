#include<SoftwareSerial.h>
SoftwareSerial serial(9,10);
int analogValue = 1;
void setup()
{
  serial.begin(9600);
}

void loop()
{

  // print it out in many formats:
  serial.print(analogValue);         // print as an ASCII-encoded decimal
  serial.print("\t");                // print a tab character
 
  serial.println();                  // print a linefeed character

  // delay 10 milliseconds before the next reading:
  delay(1000);
  analogValue++;
}
