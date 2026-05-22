#pragma once

#include <functional>

namespace taptune {

enum class AppState { Boot, Idle, Connecting, Connected, Streaming };
enum class AppEvent {
    BootCompleted, NfcTapped, BluetoothConnected,
    BluetoothDisconnected, StreamingStarted, StreamingStopped
};

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
