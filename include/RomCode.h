//
// Created by Vitalii Arkusha on 21.12.2020.
//

#ifndef KEY_DUBLICATOR_ROMCODE_H
#define KEY_DUBLICATOR_ROMCODE_H

#include "Arduino.h"

class RomCode {
public:
    RomCode();
    void setData(const byte *buf, uint8_t count);
    const byte *getData() const;

    bool isCrcValid() const;
    byte getFamilyCode() const;
    byte getCrc() const;
    void getSerialNumber(byte *buf, uint8_t count) const;


    void printDebug(HardwareSerial &serial) const;

    bool operator==(const RomCode &rhs) const;
    bool operator!=(const RomCode &rhs) const;

private:
    byte buff[8]{};
};


#endif //KEY_DUBLICATOR_ROMCODE_H
