#pragma once

#include <Wire.h>

#include "common.h"

namespace M5Stack {

class PaHub {
public:
    static const uint8_t DEFAULT_I2C_ADDRESS = 0x70;
    enum Channels {
        CH1 = 0b00000001,
        CH2 = 0b00000010,
        CH3 = 0b00000100,
        CH4 = 0b00001000,
        CH5 = 0b00010000,
        CH6 = 0b00100000,
        ALL = 0b00111111,
    };

    PaHub(TwoWire& wire = Wire, uint8_t addr = DEFAULT_I2C_ADDRESS);
    virtual ~PaHub(void);

    virtual bool begin(void);
    virtual bool enable(Channels ch);
    virtual bool isEnabled(Channels ch) const;
    virtual bool disable(Channels ch);

protected:
    virtual uint8_t getState(void) const;
    virtual bool setState(uint8_t chs);

private:
    TwoWire& _wire;
    uint8_t _addr;
};

}  // namespace M5Stack