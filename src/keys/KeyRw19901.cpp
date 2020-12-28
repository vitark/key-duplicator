//
// Created by Vitalii Arkusha on 23.12.2020.
// Some ideas was taken here. Thanks.
// https://github.com/AlexMalov/EasyKeyDublicator/blob/master/EasyKeyDublicator/EasyKeyDublicator.ino
//

#include "keys/KeyRw19901.h"

bool KeyRw19901::isRecognized(OneWire &oneWire) {
    oneWire.reset();
    oneWire.write(0xD1);    // trying to enable write bit RW-1990.1
    oneWire.write_bit(0);   // enable write (0 - enable, 1 - disable)
    delay(10);

    oneWire.reset();
    oneWire.write(0xB5); // send 0xB5 - read write flag

    if (oneWire.read() == 0xFE){
        oneWire.reset();
        oneWire.write(0xD1);  // disable write
        oneWire.write_bit(1); // set bit to disable writing
        return true;
    }

    return false;
}

bool KeyRw19901::write(const RomCode &rom, OneWire &oneWire) {
    oneWire.reset();
    // enable writing
    oneWire.write(0xD1);       // send 0xD1 - write register
    oneWire.write_bit(0);      // enable write (0 - enable, 1 - disable)
    delay(10);

    oneWire.reset();
    oneWire.write(0xD5);        // command for write
    const byte *originalKeyData = rom.getData();
    for (uint8_t i=0; i<8; ++i) {
        byte byteToWrite = ~originalKeyData[i]; // inverted data must be write RW1990.1
        for(uint8_t j=0; j<8; ++j){
            oneWire.write_bit(byteToWrite & (byte)1);
            delay(5);
            byteToWrite = byteToWrite >> (byte)1;
        }
    }

    // disable writing.
    oneWire.write(0xD1);
    oneWire.write_bit(1);
    delay(10);

    byte buff[8];
    oneWire.reset_search();
    if (!oneWire.search(buff)) {
        return false;
    }

    return memcmp(buff, originalKeyData, sizeof(buff)) == 0;
}
