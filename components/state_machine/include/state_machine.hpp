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

    /**
     * @brief Constructs the state machine with a callback invoked at every transition.
     * @param cb Function to call with the new state.
     */
    explicit StateMachine(StateCallback cb);

    /**
     * @brief Dispatches an event to the state machine, possibly triggering a transition.
     * @param event The event to process.
     */
    void dispatch(AppEvent event);

    /**
     * @brief Returns the current application state.
     * @return AppState The current state.
     */
    AppState getState() const;

private:
    AppState state_ = AppState::Boot;
    StateCallback callback_;
};

} // namespace taptune
