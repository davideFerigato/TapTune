#!/bin/bash
cd "$(dirname "$0")/test_native"
cmake -S . -B build && cmake --build build && ./build/test_state_machine
