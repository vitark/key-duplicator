//
// Created by Vitalii Arkusha on 30.12.2020.
//

#ifndef KEY_DUBLICATOR_KEYTM01A_H
#define KEY_DUBLICATOR_KEYTM01A_H

#include "IButton.h"

struct KeyTm01A {
    static bool isRecognized(OneWire &oneWire);
    static bool write(const RomCode &rom, OneWire &oneWire);
};


#endif //KEY_DUBLICATOR_KEYTM01A_H
