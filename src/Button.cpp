//
// Created by Vitalii Arkusha on 22.12.2020.
// @see https://arduinogetstarted.com/tutorials/arduino-button-long-press-short-press
//

#include "Button.h"

const int SHORT_PRESS_TIME = 500;
const int LONG_PRESS_TIME  = 2500;

Button::Button(uint8_t pin) :
mButton(pin) {
    mButton.setDebounceTime(50);
}

void Button::loop() {
    mButton.loop();

    if(mButton.isPressed()){
        pressedTime = millis();
        isPressing = true;
        isLongDetected = false;
    }

    if(mButton.isReleased()) {
        isPressing = false;
        releasedTime = millis();

        unsigned long pressDuration = releasedTime - pressedTime;

        if(pressDuration < SHORT_PRESS_TIME) {
            if (onShortPress != nullptr) {
                onShortPress();
            }
        }
    }

    if(isPressing == true && isLongDetected == false) {
        unsigned long pressDuration = millis() - pressedTime;
        if( pressDuration > LONG_PRESS_TIME ) {
            isLongDetected = true;
            if (onLongPress != nullptr) {
                onLongPress();
            }
        }
    }
}

void Button::attachHandlerShortPress(OnButtonCallback cb) {
    onShortPress = *cb;
}

void Button::attachHandlerLongPress(OnButtonCallback cb) {
    onLongPress = *cb;
}
