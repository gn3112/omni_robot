#include <AccelStepper.h>
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define X_MIN_PIN           3
#define X_MAX_PIN           2

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

#define E_STEP_PIN         26
#define E_DIR_PIN          28
#define E_ENABLE_PIN       24

#define PUSH_PIN 32

AccelStepper RightFrontWheel(1, 46, 48);   // (Type:driver, STEP, DIR) - Stepper1
AccelStepper LeftBackWheel(1, A0, A1);   // (Type:driver, STEP, DIR) - Stepper1
AccelStepper RightBackWheel(1, A6, A7);   // (Type:driver, STEP, DIR) - Stepper1
AccelStepper LeftFrontWheel(1, 26, 28);   // (Type:driver, STEP, DIR) - Stepper1

int wheelSpeed = 100;

int joyPin0 = 3;
int joyPin1 = 4;
int value0 = 0;
int value1 = 0;

bool stepper_off = false;
int s=0;
int r=1;

void setup() {
  // put your setup code here, to run once:
  LeftBackWheel.setMaxSpeed(3000);
  RightBackWheel.setMaxSpeed(3000);
  LeftFrontWheel.setMaxSpeed(3000);
  RightFrontWheel.setMaxSpeed(3000);
//  LeftBackWheel.setAcceleration(800);
//  RightBackWheel.setAcceleration(800);
//  LeftFrontWheel.setAcceleration(800);
//  RightFrontWheel.setAcceleration(800);
//  
  pinMode(X_ENABLE_PIN, OUTPUT);
  pinMode(Y_ENABLE_PIN, OUTPUT);  
  pinMode(Z_ENABLE_PIN, OUTPUT);
  pinMode(E_ENABLE_PIN, OUTPUT);

  pinMode(PUSH_PIN, INPUT);

  digitalWrite(X_ENABLE_PIN, LOW);
  digitalWrite(Y_ENABLE_PIN, LOW);
  digitalWrite(Z_ENABLE_PIN, LOW);
  digitalWrite(E_ENABLE_PIN, LOW);
 
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()>0) {
    s = r * (Serial.read() - '0');
    }

  if (s == 0){
    stopMoving();
    }
  else if (s == 1){
    moveForward();
  }
  else if (s == 2){
    moveBackward();
  }
  else if (s == 3){
    moveSidewaysRight();
  }
  else if (s == 4){
    moveSidewaysLeft();
  }
//  if (digitalRead(PUSH_PIN) == LOW and stepper_off==false){
//    stepper_off = true;
//  }
//  else if (digitalRead(PUSH_PIN) == LOW and stepper_off==true) {
//    stepper_off = false;
//  }

//  if (value1 > 800) {
//    moveForward();
//    }
//  else if (value1 < 250){
//    moveBackward();
//    }
//
//  if (value0 > 800) {
//    moveSidewaysRight();
//  }
//  else if (value0 < 250){
//    moveSidewaysLeft();
//  }
//  
//  if (stepper_off) {
//    stopMoving();
//  }
  LeftFrontWheel.runSpeed();
  LeftBackWheel.runSpeed();
  RightFrontWheel.runSpeed();
  RightBackWheel.runSpeed();
  
}

void moveForward() {
  LeftFrontWheel.setSpeed(wheelSpeed);
  LeftBackWheel.setSpeed(wheelSpeed);
  RightFrontWheel.setSpeed(wheelSpeed);
  RightBackWheel.setSpeed(wheelSpeed);
}
void moveBackward() {
  LeftFrontWheel.setSpeed(-wheelSpeed);
  LeftBackWheel.setSpeed(-wheelSpeed);
  RightFrontWheel.setSpeed(-wheelSpeed);
  RightBackWheel.setSpeed(-wheelSpeed);
}
void moveSidewaysRight() {
  LeftFrontWheel.setSpeed(wheelSpeed);
  LeftBackWheel.setSpeed(-wheelSpeed);
  RightFrontWheel.setSpeed(wheelSpeed);
  RightBackWheel.setSpeed(-wheelSpeed);
}
void moveSidewaysLeft() {
  LeftFrontWheel.setSpeed(-wheelSpeed);
  LeftBackWheel.setSpeed(wheelSpeed);
  RightFrontWheel.setSpeed(wheelSpeed);
  RightBackWheel.setSpeed(-wheelSpeed);
}
void rotateLeft() {
  LeftFrontWheel.setSpeed(-wheelSpeed);
  LeftBackWheel.setSpeed(-wheelSpeed);
  RightFrontWheel.setSpeed(wheelSpeed);
  RightBackWheel.setSpeed(wheelSpeed);
}
void rotateRight() {
  LeftFrontWheel.setSpeed(wheelSpeed);
  LeftBackWheel.setSpeed(wheelSpeed);
  RightFrontWheel.setSpeed(-wheelSpeed);
  RightBackWheel.setSpeed(-wheelSpeed);
}
void moveRightForward() {
  LeftFrontWheel.setSpeed(wheelSpeed);
  LeftBackWheel.setSpeed(0);
  RightFrontWheel.setSpeed(0);
  RightBackWheel.setSpeed(wheelSpeed);
}
void moveRightBackward() {
  LeftFrontWheel.setSpeed(0);
  LeftBackWheel.setSpeed(-wheelSpeed);
  RightFrontWheel.setSpeed(-wheelSpeed);
  RightBackWheel.setSpeed(0);
}
void moveLeftForward() {
  LeftFrontWheel.setSpeed(0);
  LeftBackWheel.setSpeed(wheelSpeed);
  RightFrontWheel.setSpeed(wheelSpeed);
  RightBackWheel.setSpeed(0);
}
void moveLeftBackward() {
  LeftFrontWheel.setSpeed(-wheelSpeed);
  LeftBackWheel.setSpeed(0);
  RightFrontWheel.setSpeed(0);
  RightBackWheel.setSpeed(-wheelSpeed);
}
void stopMoving() {
  LeftFrontWheel.setSpeed(0);
  LeftBackWheel.setSpeed(0);
  RightFrontWheel.setSpeed(0);
  RightBackWheel.setSpeed(0);
}
void disable() {
  LeftFrontWheel.disableOutputs();
  LeftBackWheel.disableOutputs();
  RightFrontWheel.disableOutputs();
  RightBackWheel.disableOutputs();
}

void enable() {
  LeftFrontWheel.enableOutputs();
  LeftBackWheel.enableOutputs();
  RightFrontWheel.enableOutputs();
  RightBackWheel.enableOutputs();
}
