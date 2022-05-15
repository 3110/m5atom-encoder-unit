#include <M5Atom.h>

#include "EncoderUnit.h"

#ifdef TARGET_M5ATOM
#define M5_BEGIN M5.begin(ENABLE_SERIAL, ENABLE_I2C, ENABLE_DISPLAY)
const bool ENABLE_SERIAL = true;
const bool ENABLE_I2C = false;     // default: true
const bool ENABLE_DISPLAY = true;  // default: false
const int SDA_PIN = 26;
const int SCL_PIN = 32;
#else
#error "You have to define correct target."
#endif

using namespace M5Stack;

EncoderUnit encoder;

void setup(void) {
    M5_BEGIN;
    Wire.begin(SDA_PIN, SCL_PIN, EncoderUnit::FREQUENCY);
    if (!encoder.begin()) {
        SERIAL_PRINTLN("Failed to initialize encoder unit.");
        while (true) {
        }
    }
}

short prev = 0;

void loop(void) {
    M5.update();
    const short cur = encoder.getValue();
    SERIAL_PRINTF_LN("Value: %d", cur);
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
        encoder.reset();
    }
    delay(20);
}