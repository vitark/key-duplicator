//
// Created by Vitalii Arkusha on 21.12.2020.
//

#include "IButton.h"
#include "keys/KeyRw19901.h"
#include "keys/KeyRw19902.h"
#include "keys/KeyTm01A.h"

IButton::IButton(uint8_t pin) :
    oneWire(pin) {
}

IButton::Family IButton::getFamily(const RomCode &data) const{
    byte familyCode = data.getFamilyCode();
    return Family(familyCode);
}

bool IButton::search(RomCode &data) {
    byte buff[8];
    oneWire.reset_search();
    if (!oneWire.search(buff)) {
        return false;
    }

    data.setData(buff, sizeof(buff));
    return true;
}

bool IButton::write(RomCode &data) {
    if (KeyRw19901::isRecognized(oneWire)) {
        return KeyRw19901::write(data, oneWire);
    }

    if (KeyRw19902::isRecognized(oneWire)) {
        return KeyRw19902::write(data, oneWire);
    }

    if (KeyTm01A::isRecognized(oneWire)) { // Always TRUE, trying to write as TM-01x (will be fixed if solution to recognize TM-01A be found)
        return KeyTm01A::write(data, oneWire);
    }

    return false;
}
