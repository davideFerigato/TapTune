#pragma once

namespace taptune::config {

constexpr char kDeviceName[]   = "TapTune";
constexpr int  kI2cClockHz     = 400000;
constexpr int  kSerialBaudRate = 115200;
constexpr bool kNfcEnabled     = true;
constexpr bool kDisplayEnabled = true;
constexpr bool kBuzzerEnabled  = true;

} // namespace taptune::config
