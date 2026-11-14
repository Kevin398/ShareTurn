#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
mkdir -p build
g++ -std=c++11 -Wall -Wextra -Werror -pedantic \
  firmware/shareturn/control.cpp simulator/main.cpp -o build/shareturn_simulator
./build/shareturn_simulator
