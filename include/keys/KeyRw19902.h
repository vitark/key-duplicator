//
// Created by Vitalii Arkusha on 23.12.2020.
//

#ifndef KEY_DUBLICATOR_KEYRW19902_H
#define KEY_DUBLICATOR_KEYRW19902_H

#include "IButton.h"

struct KeyRw19902 {
    static bool isRecognized(OneWire &oneWire);
    static bool write(const RomCode &rom, OneWire &oneWire);
};


#endif //KEY_DUBLICATOR_KEYRW19902_H
