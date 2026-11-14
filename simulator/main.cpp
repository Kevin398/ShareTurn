#include <iostream>
#include <sstream>
#include <string>
#include "../firmware/shareturn/control.h"

int main() {
  shareturn::Controller controller;
  std::cout << "ShareTurn host simulator (no Arduino needed)\n"
               "Enter simulated potentiometer reading 0..1023.\n"
               "First enter around 512 to arm. Type q to quit.\n";
  std::string line;
  while (std::getline(std::cin, line)) {
    if (line == "q" || line == "quit") break;
    std::istringstream input(line);
    int reading;
    char extra;
    if (!(input >> reading) || (input >> extra)) {
      std::cout << "Please enter a single integer (or q).\n";
      continue;
    }
    const shareturn::MotorCommand cmd = controller.update(reading);
    std::cout << "armed=" << (controller.isArmed() ? "yes" : "no")
              << " direction=" << cmd.direction
              << " rpm=" << cmd.rpm << "\n";
  }
  return 0;
}
