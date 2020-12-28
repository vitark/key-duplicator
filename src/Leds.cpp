//
// Created by Vitalii Arkusha on 20.12.2020.
//

#include "Leds.h"

Leds::Leds(uint8_t pinRed, uint8_t pinGreen) :
        pinRed(pinRed), pinGreen(pinGreen) {

    pinMode(pinRed, OUTPUT);
    pinMode(pinGreen, OUTPUT);
}

void Leds::blinkRed(uint32_t ms, bool OffOnOff) const {
    activateRed(OffOnOff);
    delay(ms/2);
    activateRed(!OffOnOff);
    delay(ms/2);
}

void Leds::blinkGreen(uint32_t ms, bool OffOnOff) const {
    activateGreen(OffOnOff);
    delay(ms/2);
    activateGreen(!OffOnOff);
    delay(ms/2);
}

void Leds::blinkRedGreen(uint32_t ms, bool OffOnOff) const {
    activateRed(OffOnOff);
    activateGreen(OffOnOff);

    delay(ms/2);

    activateRed(!OffOnOff);
    activateGreen(!OffOnOff);

    delay(ms/2);
}

void Leds::activateRed(bool on) const {
    digitalWrite(pinRed, on ? HIGH : LOW);
}

void Leds::activateGreen(bool on) const {
    digitalWrite(pinGreen, on ? HIGH : LOW);
}
