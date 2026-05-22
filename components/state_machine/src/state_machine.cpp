#include "state_machine.hpp"

namespace taptune {

StateMachine::StateMachine(StateCallback cb) : callback_(std::move(cb)) {
    callback_(state_);
}

void StateMachine::dispatch(AppEvent event) {
    switch (state_) {
        case AppState::Boot:
            if (event == AppEvent::BootCompleted) {
                state_ = AppState::Idle;
            }
            break;

        case AppState::Idle:
            if (event == AppEvent::NfcTapped) {
                state_ = AppState::Connecting;
            }
            break;

        case AppState::Connecting:
            if (event == AppEvent::BluetoothConnected) {
                state_ = AppState::Connected;
            } else if (event == AppEvent::BluetoothDisconnected) {
                state_ = AppState::Idle;
            }
            break;

        case AppState::Connected:
            if (event == AppEvent::StreamingStarted) {
                state_ = AppState::Streaming;
            } else if (event == AppEvent::BluetoothDisconnected) {
                state_ = AppState::Idle;
            }
            break;

        case AppState::Streaming:
            if (event == AppEvent::StreamingStopped) {
                state_ = AppState::Connected;
            } else if (event == AppEvent::BluetoothDisconnected) {
                state_ = AppState::Idle;
            }
            break;
    }
    callback_(state_);
}

AppState StateMachine::getState() const {
    return state_;
}

} // namespace taptune
