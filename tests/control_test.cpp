#include <cassert>
#include <iostream>
#include "../firmware/shareturn/control.h"

using shareturn::Controller;
using shareturn::MotorCommand;

void expectStop(const MotorCommand& cmd) {
  assert(cmd.direction == 0);
  assert(cmd.rpm == 0);
}

void testStartupInterlock() {
  Controller controller;
  assert(!controller.isArmed());
  expectStop(controller.update(0));
  expectStop(controller.update(1023));
  assert(!controller.isArmed());
  expectStop(controller.update(512));
  assert(controller.isArmed());
  MotorCommand cmd = controller.update(1023);
  assert(cmd.direction == 1 && cmd.rpm == 7);
}

void testStopZone() {
  Controller controller;
  controller.update(512);  // arm
  for (int raw = 422; raw <= 602; ++raw) {
    expectStop(controller.update(raw));
  }
  assert(controller.update(421).direction == -1);
  assert(controller.update(603).direction == 1);
  expectStop(controller.update(512));
}

void testDirectionsAndClamping() {
  Controller controller;
  controller.update(512);
  MotorCommand left = controller.update(0);
  MotorCommand right = controller.update(1023);
  assert(left.direction == -1 && left.rpm == 7);
  assert(right.direction == 1 && right.rpm == 7);
  assert(controller.update(-100).direction == -1);
  assert(controller.update(3000).direction == 1);
}

void testSpeedMonotonicAndLimits() {
  Controller controller;
  controller.update(512);
  int prevRight = 0;
  for (int raw = 603; raw <= 1023; ++raw) {
    const MotorCommand cmd = controller.update(raw);
    assert(cmd.direction == 1);
    assert(cmd.rpm >= 2 && cmd.rpm <= 7);
    assert(cmd.rpm >= prevRight);
    prevRight = cmd.rpm;
  }
  int prevLeft = 0;
  for (int raw = 421; raw >= 0; --raw) {
    const MotorCommand cmd = controller.update(raw);
    assert(cmd.direction == -1);
    assert(cmd.rpm >= 2 && cmd.rpm <= 7);
    assert(cmd.rpm >= prevLeft);
    prevLeft = cmd.rpm;
  }
}

int main() {
  testStartupInterlock();
  testStopZone();
  testDirectionsAndClamping();
  testSpeedMonotonicAndLimits();
  std::cout << "PASS: startup interlock, stop zone, direction, clamp, speed bounds\n";
  return 0;
}
