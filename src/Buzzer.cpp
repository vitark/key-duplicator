//
// Created by Vitalii Arkusha on 20.12.2020.
//

#include "Buzzer.h"

Buzzer::Buzzer(uint8_t pin) :
        pin(pin) {
    pinMode(pin, OUTPUT);
}

void Buzzer::beep() const {
    tone(pin, 1000);
    delay(100);
    noTone(pin);
}

void Buzzer::ok() const {
    for (int i = 400; i < 6000; i = i + 600) {
        tone(pin, i);
        delay(20);
    }
    noTone(pin);
}

void Buzzer::next() const {
    for (int i = 2500; i < 6000; i = i + 600) {
        tone(pin, i);
        delay(10);
    }
    noTone(pin);
}


void Buzzer::error() const {
    for (int j = 0; j < 3; j++) {
        for (int i = 1000; i < 2500; i=i+140) {
            tone(pin, i);
            delay(10);
        }
        delay(50);
    }
    noTone(pin);
}

