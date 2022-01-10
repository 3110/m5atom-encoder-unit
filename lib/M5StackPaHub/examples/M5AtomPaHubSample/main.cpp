#include <M5Atom.h>

#include "EncoderUnit.h"
#include "PaHub.h"

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
PaHub hub;

void setup(void) {
    M5_BEGIN;
    if (!encoder.begin(SDA_PIN, SCL_PIN)) {
        SERIAL_PRINTLN("Failed to initialize encoder unit.");
        while (true) {
        }
    }
    hub.begin();
}

bool isLEDOn = false;

void loop(void) {
    M5.update();
    if (M5.Btn.wasPressed()) {
        isLEDOn = !isLEDOn;
        hub.enable(PaHub::Channels::ALL);
        if (isLEDOn) {
            encoder.setLED(EncoderUnit::LEDPosition::BOTH, 0x00FF00);
        } else {
            encoder.setLED(EncoderUnit::LEDPosition::BOTH, 0x000000);
        }
        hub.disable(PaHub::Channels::ALL);
    }
    delay(20);
}