#include <iostream>
#include <cassert>
#include "state_machine.hpp"

using namespace taptune;

static AppState lastState = AppState::Boot;
static int callbackCount = 0;

void stateCallback(AppState s) {
    lastState = s;
    ++callbackCount;
}

void resetCounters() {
    callbackCount = 0;
}

int main() {
    // Test 1: Boot → Idle
    {
        StateMachine sm(stateCallback);
        assert(sm.getState() == AppState::Boot);
        sm.dispatch(AppEvent::BootCompleted);
        assert(sm.getState() == AppState::Idle);
        assert(callbackCount > 0);
        resetCounters();
    }

    // Test 2: Idle → Connecting
    {
        StateMachine sm(stateCallback);
        sm.dispatch(AppEvent::BootCompleted);
        sm.dispatch(AppEvent::NfcTapped);
        assert(sm.getState() == AppState::Connecting);
    }

    // Test 3: Connecting → Connected
    {
        StateMachine sm(stateCallback);
        sm.dispatch(AppEvent::BootCompleted);
        sm.dispatch(AppEvent::NfcTapped);
        sm.dispatch(AppEvent::BluetoothConnected);
        assert(sm.getState() == AppState::Connected);
    }

    // Test 4: Connected → Streaming
    {
        StateMachine sm(stateCallback);
        sm.dispatch(AppEvent::BootCompleted);
        sm.dispatch(AppEvent::NfcTapped);
        sm.dispatch(AppEvent::BluetoothConnected);
        sm.dispatch(AppEvent::StreamingStarted);
        assert(sm.getState() == AppState::Streaming);
    }

    // Test 5: Streaming → Connected on stop
    {
        StateMachine sm(stateCallback);
        sm.dispatch(AppEvent::BootCompleted);
        sm.dispatch(AppEvent::NfcTapped);
        sm.dispatch(AppEvent::BluetoothConnected);
        sm.dispatch(AppEvent::StreamingStarted);
        sm.dispatch(AppEvent::StreamingStopped);
        assert(sm.getState() == AppState::Connected);
    }

    // Test 6: Disconnect from Connected
    {
        StateMachine sm(stateCallback);
        sm.dispatch(AppEvent::BootCompleted);
        sm.dispatch(AppEvent::NfcTapped);
        sm.dispatch(AppEvent::BluetoothConnected);
        sm.dispatch(AppEvent::BluetoothDisconnected);
        assert(sm.getState() == AppState::Idle);
    }

    // Test 7: Invalid event ignored
    {
        StateMachine sm(stateCallback);
        sm.dispatch(AppEvent::BootCompleted);
        AppState before = sm.getState();
        sm.dispatch(AppEvent::StreamingStarted);
        assert(sm.getState() == before);
    }

    std::cout << "All state machine tests passed!" << std::endl;
    return 0;
}
