//
// Created by Vitalii Arkusha on 20.12.2020.
//

#ifndef KEY_DUBLICATOR_LEDS_H
#define KEY_DUBLICATOR_LEDS_H

#include <Arduino.h>


class Leds {
public:
    Leds(uint8_t pinRed, uint8_t pinGreen);
    void blinkRed(uint32_t ms = 100, bool OffOnOff = true) const;
    void blinkGreen(uint32_t ms = 100, bool OffOnOff = true) const;
    void blinkRedGreen(uint32_t ms = 100, bool OffOnOff = true) const;

    void activateRed(bool on = true) const;
    void activateGreen(bool on = true) const;
private:
    uint8_t pinRed;
    uint8_t pinGreen;
};


#endif //KEY_DUBLICATOR_LEDS_H
