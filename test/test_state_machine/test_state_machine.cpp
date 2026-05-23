#include <unity.h>
#include "state_machine.hpp"

using namespace taptune;

static AppState lastState = AppState::Boot;
static int callbackCount = 0;

void stateCallback(AppState s) {
    lastState = s;
    callbackCount++;
}

void setUp(void) {
    callbackCount = 0;
    lastState = AppState::Boot;
}

void tearDown(void) {}

void test_boot_to_idle(void) {
    StateMachine sm(stateCallback);
    TEST_ASSERT_EQUAL(AppState::Boot, sm.getState());
    sm.dispatch(AppEvent::BootCompleted);
    TEST_ASSERT_EQUAL(AppState::Idle, sm.getState());
    TEST_ASSERT_TRUE(callbackCount > 0);
}

void test_idle_to_connecting(void) {
    StateMachine sm(stateCallback);
    sm.dispatch(AppEvent::BootCompleted);
    int prev = callbackCount;
    sm.dispatch(AppEvent::NfcTapped);
    TEST_ASSERT_EQUAL(AppState::Connecting, sm.getState());
    TEST_ASSERT_TRUE(callbackCount > prev);
}

void test_connecting_to_connected(void) {
    StateMachine sm(stateCallback);
    sm.dispatch(AppEvent::BootCompleted);
    sm.dispatch(AppEvent::NfcTapped);
    sm.dispatch(AppEvent::BluetoothConnected);
    TEST_ASSERT_EQUAL(AppState::Connected, sm.getState());
}

void test_connected_to_streaming(void) {
    StateMachine sm(stateCallback);
    sm.dispatch(AppEvent::BootCompleted);
    sm.dispatch(AppEvent::NfcTapped);
    sm.dispatch(AppEvent::BluetoothConnected);
    sm.dispatch(AppEvent::StreamingStarted);
    TEST_ASSERT_EQUAL(AppState::Streaming, sm.getState());
}

void test_streaming_to_connected_on_stop(void) {
    StateMachine sm(stateCallback);
    sm.dispatch(AppEvent::BootCompleted);
    sm.dispatch(AppEvent::NfcTapped);
    sm.dispatch(AppEvent::BluetoothConnected);
    sm.dispatch(AppEvent::StreamingStarted);
    sm.dispatch(AppEvent::StreamingStopped);
    TEST_ASSERT_EQUAL(AppState::Connected, sm.getState());
}

void test_disconnect_from_connected(void) {
    StateMachine sm(stateCallback);
    sm.dispatch(AppEvent::BootCompleted);
    sm.dispatch(AppEvent::NfcTapped);
    sm.dispatch(AppEvent::BluetoothConnected);
    sm.dispatch(AppEvent::BluetoothDisconnected);
    TEST_ASSERT_EQUAL(AppState::Idle, sm.getState());
}

void test_invalid_event_ignored(void) {
    StateMachine sm(stateCallback);
    sm.dispatch(AppEvent::BootCompleted);
    AppState before = sm.getState();
    // StreamStarted while Idle should not change state
    sm.dispatch(AppEvent::StreamingStarted);
    TEST_ASSERT_EQUAL(before, sm.getState());
}

void runAllTests(void) {
    RUN_TEST(test_boot_to_idle);
    RUN_TEST(test_idle_to_connecting);
    RUN_TEST(test_connecting_to_connected);
    RUN_TEST(test_connected_to_streaming);
    RUN_TEST(test_streaming_to_connected_on_stop);
    RUN_TEST(test_disconnect_from_connected);
    RUN_TEST(test_invalid_event_ignored);
}

extern "C" void app_main() {
    UNITY_BEGIN();
    runAllTests();
    UNITY_END();
}
