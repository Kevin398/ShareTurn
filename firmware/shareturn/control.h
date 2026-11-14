#ifndef SHARETURN_CONTROL_H
#define SHARETURN_CONTROL_H

namespace shareturn {

// Motor direction relative to the raw knob reading, NOT guaranteed physical
// clockwise/counterclockwise until the motor mounting has been tested.
struct MotorCommand {
  int direction;  // -1, 0, +1
  int rpm;        // 0 when stopped, otherwise [2, 7]
};

// Hardware-independent input interpretation. Works on Arduino and desktop C++.
class Controller {
 public:
  Controller();
  MotorCommand update(int analogReading);
  bool isArmed() const;

 private:
  bool armed_;
};

}  // namespace shareturn

#endif
