#include "EncoderUnit.h"

namespace M5Stack {

EncoderUnit::EncoderUnit(TwoWire& wire, uint8_t addr)
    : _wire(wire), _addr(addr) {
}

EncoderUnit::~EncoderUnit(void) {
}

bool EncoderUnit::begin(int sdaPin, int sclPin, uint32_t frequency) {
    return this->_wire.begin(sdaPin, sclPin, frequency);
}

bool EncoderUnit::isPressed(void) const {
    uint8_t result = 0xFF;
    readBytes(this->_addr, BUTTON, &result, sizeof(result));
    return result == 0;
}

short EncoderUnit::getValue(void) const {
    uint8_t data[2] = {0};
    readBytes(this->_addr, ENCODER, data, sizeof(data));
    return static_cast<short>(data[0] | (data[1] << 8));
}

void EncoderUnit::setLED(LEDPosition pos, uint32_t color) {
    const uint8_t data[] = {static_cast<uint8_t>(pos),
                            static_cast<uint8_t>((color >> 16) & 0xFF),
                            static_cast<uint8_t>((color >> 8) & 0xFF),
                            static_cast<uint8_t>(color & 0xFF)};
    writeBytes(this->_addr, RGB_LED, data, sizeof(data));
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