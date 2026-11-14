#include <Stepper.h>
#include "control.h"

// Verify motor label: intended for the kit's 5V 28BYJ-48 + ULN2003.
// ULN2003 IN1=D8, IN2=D9, IN3=D10, IN4=D11.
// Stepper constructor order MUST be IN1, IN3, IN2, IN4.
const int kStepsPerRevolution = 2048;  // Approx. geared output full-steps/rev
const int kIn1 = 8;
const int kIn2 = 9;
const int kIn3 = 10;
const int kIn4 = 11;
const int kKnobPin = A0;

Stepper trayMotor(kStepsPerRevolution, kIn1, kIn3, kIn2, kIn4);
shareturn::Controller controller;

int previousDirection = 0;
int previousRpm = 0;
unsigned long lastDebugMs = 0;

void releaseMotor() {
  // The built-in Stepper library leaves coils powered at stop otherwise.
  digitalWrite(kIn1, LOW);
  digitalWrite(kIn2, LOW);
  digitalWrite(kIn3, LOW);
  digitalWrite(kIn4, LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(kKnobPin, INPUT);
  trayMotor.setSpeed(2);
  releaseMotor();
  Serial.println(F("ShareTurn: turn knob to centre before motor starts."));
}

void loop() {
  const int knob = analogRead(kKnobPin);
  const shareturn::MotorCommand cmd = controller.update(knob);

  if (millis() - lastDebugMs >= 500) {
    lastDebugMs = millis();
    Serial.print(F("knob="));
    Serial.print(knob);
    Serial.print(F(" armed="));
    Serial.print(controller.isArmed() ? F("yes") : F("no"));
    Serial.print(F(" direction="));
    Serial.print(cmd.direction);
    Serial.print(F(" rpm="));
    Serial.println(cmd.rpm);
  }

  if (cmd.direction == 0) {
    // Release only on the transition to stopped (not on every loop).
    if (previousDirection != 0) releaseMotor();
    previousDirection = 0;
    previousRpm = 0;
    return;
  }

  if (cmd.rpm != previousRpm) {
    trayMotor.setSpeed(cmd.rpm);
    previousRpm = cmd.rpm;
  }
  previousDirection = cmd.direction;

  // One step per loop: input is read again right after this step, unlike a
  // blocking motor.step(2048) command that ignores the knob for seconds.
  trayMotor.step(cmd.direction);
}
