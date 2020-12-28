//
// Created by Vitalii Arkusha on 21.12.2020.
//

#include "RomCode.h"
#include <OneWire.h>

#define CRC_BYTE_POS 7
#define FAMILY_BYTE_POS 0

RomCode::RomCode() {
    for (byte &i : buff) {
        i = 0x0;
    }
}

void RomCode::setData(const byte *buf, uint8_t count) {
    count = min(count, sizeof(buff));
    for (int i = 0; i < count; i++) {
        buff[i] = buf[i];
    }
}

bool RomCode::isCrcValid() const {
    return OneWire::crc8(buff, CRC_BYTE_POS) == getCrc();
}

byte RomCode::getCrc() const {
    return buff[CRC_BYTE_POS];
}

byte RomCode::getFamilyCode() const {
    return buff[FAMILY_BYTE_POS];
}

void RomCode::getSerialNumber(byte *buf, uint8_t count) const {
    count = min(count, 6);
    for (int i = 0; i<count ; ++i) {
        buf[i] = buff[i+1];
    }
}

void RomCode::printDebug(HardwareSerial &serial) const {
    serial.write("HEX ROM Code: ");
    for (unsigned char data : buff) {
        serial.print(' ');
        serial.print(data, HEX);
    }
    serial.println();
}

bool RomCode::operator==(const RomCode &rhs) const {
    return memcmp(buff, rhs.buff, sizeof(buff)) == 0;
}

bool RomCode::operator!=(const RomCode &rhs) const {
    return memcmp(buff, rhs.buff, sizeof(buff)) != 0;
}

const byte *RomCode::getData() const {
    return buff;
}

