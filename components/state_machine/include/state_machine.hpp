#pragma once

#include <functional>

/**
 * @brief Main namespace for the TapTune embedded project.
 */
namespace taptune {

enum class AppState { Boot, Idle, Connecting, Connected, Streaming };
enum class AppEvent {
    BootCompleted, NfcTapped, BluetoothConnected,
    BluetoothDisconnected, StreamingStarted, StreamingStopped
};

/**
 * @brief Finite state machine for TapTune.
 * 
 * Manages the application's states: Boot, Idle, Connecting, Connected, Streaming.
 * Each state transition can be observed via a callback.
 */
class StateMachine {
public:
    using StateCallback = std::function<void(AppState)>;

    explicit StateMachine(StateCallback cb);
    void dispatch(AppEvent event);
    AppState getState() const;

private:
    AppState state_ = AppState::Boot;
    StateCallback callback_;
};

} // namespace taptune
