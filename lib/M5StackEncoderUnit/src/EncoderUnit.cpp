#include "EncoderUnit.h"

namespace M5Stack {

static const uint8_t RESET_REG_VALUE = 1;

EncoderUnit::EncoderUnit(TwoWire& wire, uint8_t addr)
    : _wire(wire), _addr(addr), _mode(Mode::PULSE) {
}

EncoderUnit::~EncoderUnit(void) {
}

bool EncoderUnit::begin(void) {
    return true;
}

bool EncoderUnit::isPressed(void) const {
    uint8_t result = 0xFF;
    readBytes(getAddress(), BUTTON, &result, sizeof(result));
    return result == 0;
}

short EncoderUnit::getValue(void) const {
    uint8_t data[2] = {0};
    readBytes(getAddress(), ENCODER, data, sizeof(data));
    return static_cast<short>(data[0] | (data[1] << 8));
}

void EncoderUnit::setLED(LEDPosition pos, uint32_t color) {
    const uint8_t data[] = {static_cast<uint8_t>(pos),
                            static_cast<uint8_t>((color >> 16) & 0xFF),
                            static_cast<uint8_t>((color >> 8) & 0xFF),
                            static_cast<uint8_t>(color & 0xFF)};
    writeBytes(getAddress(), RGB_LED, data, sizeof(data));
}

void EncoderUnit::reset(void) {
    writeBytes(getAddress(), RESET, &RESET_REG_VALUE, sizeof(RESET_REG_VALUE));
}

bool EncoderUnit::isPulseMode(void) const {
    return this->_mode == Mode::PULSE;
}

bool EncoderUnit::isAbsoluteMode(void) const {
    return this->_mode == Mode::AB;
}

void EncoderUnit::setPulseMode(void) {
    setMode(Mode::PULSE);
}

void EncoderUnit::setAbsoluteMode(void) {
    setMode(Mode::AB);
}

uint8_t EncoderUnit::getAddress(void) const {
    return this->_addr;
}

void EncoderUnit::setMode(Mode mode) {
    uint8_t v = static_cast<uint8_t>(mode);
    writeBytes(getAddress(), MODE, &v, sizeof(v));
    this->_mode = mode;
    SERIAL_PRINTF_LN("Mode: %s Mode",
                     this->_mode == Mode::PULSE ? "Pulse" : "Absolute");
}

bool EncoderUnit::readBytes(uint8_t addr, uint8_t reg, uint8_t* buf,
                            size_t len) const {
    this->_wire.beginTransmission(addr);
    this->_wire.write(reg);
    this->_wire.endTransmission();

    this->_wire.requestFrom(addr, len);
    for (size_t i = 0; i < len; ++i) {
        buf[i] = this->_wire.read();
    }
    return true;
}

bool EncoderUnit::writeBytes(uint8_t addr, uint8_t reg, const uint8_t* buf,
                             size_t len) {
    this->_wire.beginTransmission(addr);
    this->_wire.write(reg);
    for (size_t i = 0; i < len; ++i) {
        this->_wire.write(buf[i]);
    }
    this->_wire.endTransmission();
    return true;
}

}  // namespace M5Stack