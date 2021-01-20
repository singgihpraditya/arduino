void setup() {
  // initialize digital pin 13 as an output.
  pinMode(D0, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(D0, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(D0, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}
