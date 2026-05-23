cmake_minimum_required(VERSION 3.16)
project(tap_tune_native_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(../components/state_machine/include)
add_library(state_machine ../components/state_machine/src/state_machine.cpp)

add_executable(test_state_machine test_state_machine.cpp)
target_link_libraries(test_state_machine state_machine)
