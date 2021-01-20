#include <Servo.h>

//initiate object servo
Servo servoSteering;

float servoCenterDegree = 90;
float servoAngle = 23;
int servoPort = 2;

int motor1ForwardPort = 3;
int motor1BackwardPort = 4;
int motor1PWMPort = 5;

float bluetoothTxValue = 0;
int intBluetoothTxValue = 0;

void setup() {
  Serial.begin(9600);
  servoSteering.attach(servoPort);
  
  pinMode(motor1ForwardPort, OUTPUT);
  pinMode(motor1BackwardPort, OUTPUT);
  pinMode(motor1PWMPort, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int serialAvailable = Serial.available();
  if (serialAvailable > 0)
  {
    int newBluetoothTxValue = Serial.read();
    Serial.print("Bluetooth value");
    Serial.print(" new : ");
    Serial.print(newBluetoothTxValue);
    Serial.print(" old : ");
    Serial.println(intBluetoothTxValue);

    if (newBluetoothTxValue != intBluetoothTxValue) {
      intBluetoothTxValue = newBluetoothTxValue;
      bluetoothTxValue = (float) intBluetoothTxValue;
      if (bluetoothTxValue >= 0 && bluetoothTxValue <= 90) {
        moveServo(bluetoothTxValue);
      }
      if (bluetoothTxValue >= 90 && bluetoothTxValue <= 180) {
        moveServo(bluetoothTxValue);
      }
    }
  }
}

void moveMotor(float bluetoothTxValue) {
  Serial.print("Motor 1 move to :");
  Serial.println(bluetoothTxValue);
  int motor1Speed = 0;
  if (bluetoothTxValue > 135) {
    Serial.println("Motor 1 move forward");
    motor1Speed = (((bluetoothTxValue - 90) / 90) * 255);
    digitalWrite(motor1ForwardPort, LOW);
    digitalWrite(motor1BackwardPort, HIGH);
  }
  else {
    Serial.println("Motor 1 move backward");
    motor1Speed = (((bluetoothTxValue - 90) / 45) * 255);
    digitalWrite(motor1ForwardPort, HIGH);
    digitalWrite(motor1BackwardPort, LOW);
  }
  Serial.print(" motor1Speed : ");
  Serial.println(motor1Speed);
  analogWrite(motor1PWMPort, bluetoothTxValue); // Then inject it to our motor
}

void moveServo(float bluetoothTxValue) {
  Serial.print("Servo 1 move to : ");
  Serial.println(bluetoothTxValue);

  int servoPosition = 0;
  if (bluetoothTxValue > 45) {
    Serial.println("Servo 1 move right");
    servoPosition = servoCenterDegree + (((bluetoothTxValue - 45) / 45) * servoAngle);
  }
  else {
    Serial.println("Servo 1 move left");
    servoPosition = servoCenterDegree - (((45 - bluetoothTxValue) / 45) * servoAngle);
  }
  Serial.print(" servoPosition : ");
  Serial.println(servoPosition);
  servoSteering.write(servoPosition);
}
