//
// Created by Vitalii Arkusha on 22.12.2020.
//

#ifndef KEY_DUBLICATOR_BUTTON_H
#define KEY_DUBLICATOR_BUTTON_H

#include <Arduino.h>
#include <ezButton.h>

typedef void(*OnButtonCallback)();

class Button {
public:
    explicit Button(uint8_t pin);
    void loop();

    /**
     * @param cb callback function. Pass nullptr for deattach handler.
     */
    void attachHandlerShortPress(OnButtonCallback cb);

    /**
     * @param cb callback function. Pass nullptr for deattach handler.
     */
    void attachHandlerLongPress(OnButtonCallback cb);

private:
    ezButton mButton;

    unsigned long pressedTime  = 0;
    unsigned long releasedTime = 0;
    bool isPressing = false;
    bool isLongDetected = false;

    OnButtonCallback onShortPress = nullptr;
    OnButtonCallback onLongPress = nullptr;
};


#endif //KEY_DUBLICATOR_BUTTON_H
