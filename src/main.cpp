#include <M5Atom.h>

#include "EncoderUnit.h"

#ifdef TARGET_M5ATOM
#define M5_BEGIN M5.begin(ENABLE_SERIAL, ENABLE_I2C, ENABLE_DISPLAY)
const bool ENABLE_SERIAL = true;
const bool ENABLE_I2C = true;
const bool ENABLE_DISPLAY = true;  // default: false
const int SDA_PIN = 26;
const int SCL_PIN = 32;
#else
#error "You have to define correct target."
#endif

using namespace M5Stack;

EncoderUnit encoder;
short prev = 0;

void setup(void) {
    M5_BEGIN;
    if (!encoder.begin(SDA_PIN, SCL_PIN)) {
        SERIAL_PRINTLN("Failed to initialize encoder unit.");
        while (true) {
        }
    }
}

void loop(void) {
    M5.update();
    const short cur = encoder.getValue();
    if (prev != cur) {
        SERIAL_PRINTLN(cur);
        if (prev > cur) {
            encoder.setLED(EncoderUnit::LEDPosition::LEFT, 0x000011);
        } else {
            encoder.setLED(EncoderUnit::LEDPosition::RIGHT, 0x111100);
        }
        prev = cur;
    } else {
        encoder.setLED(EncoderUnit::LEDPosition::BOTH, 0x001100);
    }
    if (encoder.isPressed()) {
        encoder.setLED(EncoderUnit::LEDPosition::BOTH, 0xC800FF);
    }
    delay(20);
}