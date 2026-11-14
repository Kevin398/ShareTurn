#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
mkdir -p build
g++ -std=c++11 -Wall -Wextra -Werror -pedantic \
  firmware/shareturn/control.cpp tests/control_test.cpp -o build/control_test
./build/control_test
