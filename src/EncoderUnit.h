#pragma once

#include <Wire.h>

#include "common.h"

namespace M5Stack {

class EncoderUnit {
public:
    static const uint8_t I2C_ADDRESS = 0x40;
    static const uint32_t FREQUENCY = 200000L;
    static const int SDA_PIN = 21;
    static const int SCL_PIN = 22;
    enum Register { ENCODER = 0x10, BUTTON = 0x20, RGB_LED = 0x30 };
    enum LEDPosition { BOTH = 0, LEFT = 1, RIGHT = 2 };

    EncoderUnit(TwoWire& wire = Wire, uint8_t addr = I2C_ADDRESS);
    virtual ~EncoderUnit(void);

    virtual bool begin(int sdaPin = SDA_PIN, int sclPin = SCL_PIN,
                       uint32_t frequency = FREQUENCY);
    virtual bool isPressed(void) const;
    virtual void setLED(LEDPosition pos, uint32_t color);
    virtual short getValue(void) const;

protected:
    virtual uint8_t getAddress(void) const;
    virtual bool readBytes(uint8_t addr, uint8_t reg, uint8_t* buf,
                           size_t len) const;
    virtual bool writeBytes(uint8_t addr, uint8_t reg, const uint8_t* buf,
                            size_t len);

private:
    TwoWire& _wire;
    uint8_t _addr;
};

}  // namespace M5Stack