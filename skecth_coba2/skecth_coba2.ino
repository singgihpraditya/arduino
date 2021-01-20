int dataInt = 0;
char dataChar = 'c';
String dataString = "foobar";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(dataInt);
  Serial.println(dataChar);
  Serial.println(dataString);
  delay(1000);
  Serial.println("data "+dataInt);
  Serial.println("dataChar "+dataChar);
  Serial.println("dataString "+dataString);
   delay(1000);
}
