//
// Created by Vitalii Arkusha on 30.12.2020.
// See: @http://domofon-master2009.narod.ru/publ/logicheskij_analizator_i_primer_ego_primenenija_dlja_issledovanija_protokola_zapisi_zagotovki_tm_01/1-1-0-16
//

#include "keys/KeyTm01A.h"

bool KeyTm01A::isRecognized(OneWire &oneWire) {
    // Should be fixed when solution for recognize TM-01A will be found
    return true;
}

bool KeyTm01A::write(const RomCode &rom, OneWire &oneWire) {
    oneWire.reset();
    // enable writing
    oneWire.write(0xC1);       // send 0xC1 - write register
    oneWire.write_bit(1);      // enable write (1 - enable, 0 - disable)
    delay(5);

    oneWire.reset(); // ????
    oneWire.write(0xC5);        // command for write
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
    oneWire.write(0xC1);
    oneWire.write_bit(0);
    delay(30);

    byte buff[8];
    oneWire.reset_search();
    if (!oneWire.search(buff)) {
        return false;
    }

    return memcmp(buff, originalKeyData, sizeof(buff)) == 0;
}
