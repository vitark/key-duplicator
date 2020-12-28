#include <Arduino.h>

#include "Leds.h"
#include "Buzzer.h"
#include "IButton.h"
#include "RomCode.h"
#include "Button.h"

#define PIN_I_BUTTON A5
#define PIN_LED_RED 2
#define PIN_LED_GREEN 3
#define PIN_BUTTON_RW 7
#define PIN_BUZZER 12

Leds leds(PIN_LED_RED, PIN_LED_GREEN);
Buzzer buzzer(PIN_BUZZER);
IButton iButton(PIN_I_BUTTON);
Button button(PIN_BUTTON_RW);

typedef enum : uint8_t {
    WaitForReadKey,
    WaitForPressButton,
    WaitForWriteKey,
} TStates;

RomCode iButtonCode;
TStates appState;

void(* resetFunc)() = nullptr;

void longPress();
void shortPress();
void stateWaitForPressButton();

void setup() {
    Serial.begin(115200);

    leds.blinkRedGreen(200);
    buzzer.beep();
    button.attachHandlerLongPress(longPress);

    appState = WaitForReadKey;
}

void loop() {
    if (appState == WaitForReadKey) {
        leds.blinkGreen(400);

        if (iButton.search(iButtonCode)) {
            leds.activateGreen();
            buzzer.beep();

            if (iButtonCode.isCrcValid()) {
                Serial.print("Original: ");
                iButtonCode.printDebug(Serial);

                stateWaitForPressButton();
            } else {
                buzzer.error();
            }
        }
    }

    if (appState == WaitForPressButton) {
        button.loop();
    }

    if (appState == WaitForWriteKey) {
        button.loop();
        leds.blinkRed(400); // waiting for read RW keys.
        RomCode rwRom;
        if (iButton.search(rwRom)) {
            Serial.print("RW Copy: ");
            rwRom.printDebug(Serial);

            if (rwRom != iButtonCode) {
                if (iButton.write(iButtonCode)) {
                    leds.blinkRedGreen(400, false);
                    buzzer.ok();
                    Serial.println("The key copied successfully.");
                } else {
                    leds.blinkRedGreen(1000, false);
                    buzzer.error();
                    Serial.println("The key copy failed");
                }
            } else { // the keys already has the code, nothing to write
                leds.blinkRedGreen(400, false);
                buzzer.ok();
                Serial.println("It is the same key. No need to write it down.");
            }

            leds.activateRed(false);
            stateWaitForPressButton();
        }
    }
}

void stateWaitForPressButton() {
    appState = WaitForPressButton;
    button.attachHandlerShortPress(shortPress);
}

void shortPress() {
    buzzer.next();
    if (appState == WaitForPressButton) {
        button.attachHandlerShortPress(nullptr);
        appState = WaitForWriteKey;
    }
}

void longPress() {
    buzzer.ok();
    resetFunc();
}