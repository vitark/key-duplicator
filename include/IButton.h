//
// Created by Vitalii Arkusha on 21.12.2020.
//

#ifndef KEY_DUBLICATOR_IBUTTON_H
#define KEY_DUBLICATOR_IBUTTON_H

#include <Arduino.h>
#include <OneWire.h>
#include "RomCode.h"

class IButton {
public:
    typedef enum : byte {
        DS1990A = 0x01,
        DS1982U_F3  = 0x89,
    } Family;

    explicit IButton(uint8_t pin);

    // false in case device not found or does not supporting, otherwise true (CRC check should be performed separately)
    bool search(RomCode &data);
    bool write(RomCode &data);

    Family getFamily(const RomCode &data) const;



private:
    OneWire oneWire;
};


#endif //KEY_DUBLICATOR_IBUTTON_H
