//
// Created by Vitalii Arkusha on 23.12.2020.
// Some ideas was taken here. Thanks.
// https://github.com/AlexMalov/EasyKeyDublicator/blob/master/EasyKeyDublicator/EasyKeyDublicator.ino
//

#include "keys/KeyRw19902.h"

bool KeyRw19902::isRecognized(OneWire &oneWire) {
    oneWire.reset();
    oneWire.write(0x1D);    // trying to enable write bit RW-1990.1
    oneWire.write_bit(1);   // enable write (1 - enable, 0 - disable)
    delay(10);

    oneWire.reset();
    oneWire.write(0x1E); // send 0x1E - read write flag

    if (oneWire.read() == 0xFE){
        oneWire.reset();
        oneWire.write(0x1D);  // disable write RW-1990.2
        oneWire.write_bit(0); // set bit to disable writing
        return true;
    }

    return false;
}

bool KeyRw19902::write(const RomCode &rom, OneWire &oneWire) {
    oneWire.reset();
    // enable writing
    oneWire.write(0x1D);       // send 0xD1 - write register
    oneWire.write_bit(1);      // enable write (1 - enable, 0 - disable)
    delay(10);

    oneWire.reset();
    oneWire.write(0xD5);        // command for write
    const byte *originalKeyData = rom.getData();
    for (uint8_t i = 0; i<8; ++i) {
        byte byteToWrite = originalKeyData[i];
        for(uint8_t j=0; j<8; ++j){
            oneWire.write_bit(byteToWrite & (byte)1);
            delay(5);
            byteToWrite = byteToWrite >> (byte)1;
        }
    }

    // disable writing.
    oneWire.write(0x1D);
    oneWire.write_bit(0);
    delay(10);

    byte buff[8];
    oneWire.reset_search();
    if (!oneWire.search(buff)) {
        return false;
    }

    return memcmp(buff, originalKeyData, sizeof(buff)) == 0;
}
