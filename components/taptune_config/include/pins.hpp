#pragma once

namespace taptune::pins {

// Audio DAC
constexpr int kAudioLeft  = 25;
constexpr int kAudioRight = 26;

// LED RGB (common cathode)
constexpr int kLedRed   = 32;
constexpr int kLedGreen = 33;
constexpr int kLedBlue  = 27;

// Buzzer passivo (PWM LEDC)
constexpr int kBuzzer = 14;

// I2C bus
constexpr int kI2cSda = 21;
constexpr int kI2cScl = 22;

} // namespace taptune::pins
