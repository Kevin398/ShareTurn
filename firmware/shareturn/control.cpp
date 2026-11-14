#include "control.h"

namespace shareturn {
namespace {
const int kMinReading = 0;
const int kMaxReading = 1023;
const int kCenter = 512;
const int kDeadZone = 90;  // +/- 90 readings around center: STOP
const int kMinRpm = 2;
const int kMaxRpm = 7;

int clampReading(int value) {
  if (value < kMinReading) return kMinReading;
  if (value > kMaxReading) return kMaxReading;
  return value;
}

MotorCommand stopped() {
  MotorCommand cmd = {0, 0};
  return cmd;
}
}  // namespace

Controller::Controller() : armed_(false) {}

bool Controller::isArmed() const { return armed_; }

MotorCommand Controller::update(int analogReading) {
  const int reading = clampReading(analogReading);
  const int delta = reading - kCenter;
  const int magnitude = (delta < 0) ? -delta : delta;

  // Start-up interlock: a fresh board won't spin until the user centres it.
  if (!armed_) {
    if (magnitude <= kDeadZone) armed_ = true;
    return stopped();
  }

  if (magnitude <= kDeadZone) return stopped();

  // Map active knob travel to a conservative 2-7 RPM range.
  // The left and right analog spans differ by 1 count.
  const int span = (delta > 0) ? (kMaxReading - kCenter - kDeadZone)
                               : (kCenter - kMinReading - kDeadZone);
  const int activeTravel = magnitude - kDeadZone;
  const int speed = kMinRpm +
      activeTravel * (kMaxRpm - kMinRpm) / span;

  MotorCommand cmd = {(delta > 0) ? 1 : -1, speed};
  return cmd;
}

}  // namespace shareturn
