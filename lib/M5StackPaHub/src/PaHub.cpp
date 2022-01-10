#include "PaHub.h"

namespace M5Stack {

PaHub::PaHub(TwoWire& wire, uint8_t addr) : _wire(wire), _addr(addr) {
}

PaHub::~PaHub(void) {
}

bool PaHub::begin(void) {
    return true;
}

bool PaHub::enable(Channels ch) {
    const uint8_t cur = getState();
    if (cur == 0xFF) {
        return false;
    }
    return setState(cur | ch);
}

bool PaHub::isEnabled(Channels ch) const {
    const uint8_t cur = getState();
    if (cur == 0xFF) {
        return false;
    }
    return (cur & ch) == ch;
}

bool PaHub::disable(Channels ch) {
    const uint8_t cur = getState();
    if (cur == 0xFF) {
        return false;
    }
    return setState(cur & ch);
}

uint8_t PaHub::getState(void) const {
    this->_wire.requestFrom(this->_addr, static_cast<uint8_t>(1));
    if (this->_wire.available()) {
        return this->_wire.read();
    } else {
        SERIAL_PRINTLN("getState() failed");
        return 0xFF;
    }
}

bool PaHub::setState(uint8_t chs) {
    this->_wire.beginTransmission(this->_addr);
    this->_wire.write(chs);
    return this->_wire.endTransmission() != 0;
}

}  // namespace M5Stack
