int in1 = 5; //Declaring where our module is wired
int in2 = 6;
int ConA = 7;// Don't forget this is a PWM DI/DO
int speed1;
float speed2;
void setup() {
    Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);  
  pinMode(ConA, OUTPUT);
}
void TurnMotorA(){ //We create a function which control the direction and speed
  digitalWrite(in1, LOW); //Switch between this HIGH and LOW to change direction
  digitalWrite(in2, HIGH);
  speed1 = analogRead(A0);
    Serial.println(speed1);
  speed2 = (float)speed1;
  speed2 = speed2*0.2492668622; //We read thea analog value from the potentiometer calibrate it
    Serial.print(speed2);
  speed2 = (speed2/2)+127;
  Serial.println(speed2);
  analogWrite(ConA,speed2);// Then inject it to our motor
}
void loop() {
  TurnMotorA(); //one function that keeps looping you can add another one with different direction or stop
}
