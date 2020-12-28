//
// Created by Vitalii Arkusha on 20.12.2020.
//

#ifndef KEY_DUBLICATOR_BUZZER_H
#define KEY_DUBLICATOR_BUZZER_H

#include "Arduino.h"

class Buzzer {
public:
    Buzzer(uint8_t pin);
    void beep() const;
    void ok() const;
    void error() const;
    void next() const;

private:
    uint8_t pin;
};


#endif //KEY_DUBLICATOR_BUZZER_H
