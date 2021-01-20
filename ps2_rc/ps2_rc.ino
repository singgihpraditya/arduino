#include <PS2X_lib.h>
#include <Servo.h>

PS2X ps2x;
Servo servoSteering;

float servoCenterDegree = 95;
float servoAngle = 23;

int error = 0;
byte type = 0;
byte vibrate = 0;

int motor1pin1 = 4;
int motor1pin2 = 5;
int motor1PWM = 6;
int servoPin = 7;

float defaultThrotleYAxis = 128;
float defaultSteeringXAxis = 127;

void setup() {
  Serial.begin(57600);
  error = ps2x.config_gamepad(13, 11, 10, 12, true, true); //GamePad(clock, command, attention, data, Pressures?, Rumble?)
  if (error == 0) {
    Serial.println("Found Controller, configured successful");
  }
  else if (error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
  else if (error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
  else if (error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  servoSteering.attach(servoPin);

  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor1PWM, OUTPUT);
  servoSteering.write(servoCenterDegree);
}

void loop() {
  if (error == 1)
    return;

  ps2x.read_gamepad(false, vibrate);
  int currentThrotleYAxis = ps2x.Analog(PSS_LY);
  int currentSteeringXAxis = ps2x.Analog(PSS_RX);

//  Serial.print("currentThrotleYAxis : ");
//  Serial.println(currentThrotleYAxis);
//  Serial.print("currentSteeringXAxis : ");
//  Serial.println(currentSteeringXAxis);

  if (ps2x.Button(PSB_PAD_UP)) {
    Serial.print("Up held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
  }
  else if (ps2x.Button(PSB_PAD_DOWN)) {
    Serial.print("DOWN held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);
  }
  else if (defaultThrotleYAxis != currentThrotleYAxis) {
    Serial.print("Steering stick: ");
    float currentThrotleYAxisFloat = (float) currentThrotleYAxis;
    int motor1Speed = 0;
    if (currentThrotleYAxisFloat > 127) {
      Serial.println("\nMotor 1 move backward");
         digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, HIGH);
      motor1Speed = ((currentThrotleYAxisFloat - 127) * 2)-1;
      
    }
    else {
      Serial.println("\nMotor 1 move forward");
      motor1Speed = (127 - currentThrotleYAxisFloat ) * 2;
   
      digitalWrite(motor1pin1, HIGH);
      digitalWrite(motor1pin2, LOW);
    }
    Serial.print(" motor1Speed : ");
    Serial.println(motor1Speed);
    analogWrite(motor1PWM, motor1Speed);
  }
  else {
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, LOW);
  }

  if (ps2x.Button(PSB_PAD_RIGHT)) {
    Serial.print("Right held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
    servoSteering.write(servoCenterDegree + servoAngle);
  }
  else if (ps2x.Button(PSB_PAD_LEFT)) {
    Serial.print("LEFT held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
    servoSteering.write(servoCenterDegree - servoAngle);
  }
  else if (defaultSteeringXAxis != currentSteeringXAxis) {
    Serial.print("Steering stick: ");
    Serial.println(currentSteeringXAxis);
    
    float currentSteeringXAxisFloat = (float) currentSteeringXAxis;
    int servoNewAngle = servoCenterDegree;
    if (currentSteeringXAxisFloat > 127) {
      Serial.print("\nMotor 1 move right");
      servoNewAngle = ((currentSteeringXAxisFloat - 127) / 127) * servoAngle;
      servoNewAngle = servoCenterDegree + servoNewAngle;
    }
    else {
      Serial.print("\nMotor 1 move left");
      servoNewAngle = ((127 - currentSteeringXAxisFloat ) / 127) * servoAngle;
      Serial.println(servoNewAngle);
      servoNewAngle = servoCenterDegree - servoNewAngle;
    }
    Serial.print(" servoNewAngle : ");
    Serial.println(servoNewAngle);
    servoSteering.write(servoNewAngle);
  }
  else {
//    Serial.print(" servoCenterDegree : ");
//    Serial.println(servoCenterDegree);
    servoSteering.write(servoCenterDegree);
  }
  delay(50);
}
