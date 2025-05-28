#include <BufferOutputStream.h>

BufferOutputStream::BufferOutputStream(uint8_t* buffer, size_t len) {
    _buffer = Buffer(buffer, len);
    _pos = 0;
}

BufferOutputStream::BufferOutputStream(Buffer& buffer) {
    _buffer = Buffer(buffer.bytes(), buffer.length());
    _pos = 0;
}

int BufferOutputStream::available() {
    return _buffer.length() - _pos;
}

int BufferOutputStream::read() {
    return -1;
}

int BufferOutputStream::peek() {
    return -1;
}

int BufferOutputStream::availableForWrite() {
    return available();
}

size_t BufferOutputStream::write(uint8_t w) {
    if (_buffer.set(_pos, w) > 0) {
        return 1;
    }
    return 0;
}

size_t BufferOutputStream::writeBytes(const uint8_t* buffer, size_t size) {
    return _buffer.set(_pos, buffer, size);
}

int BufferOutputStream::write(uint16_t val) {
    uint8_t temp[] { 
        (uint8_t)((val >> 8) & 0xFF), 
        (uint8_t)(val & 0xFF)
    };

    return writeBytes(temp, 2);
}

int BufferOutputStream::write(uint32_t val) {
    uint8_t temp[] { 
        (uint8_t)((val >> 24) & 0xFF), 
        (uint8_t)((val >> 16) & 0xFF), 
        (uint8_t)((val >> 8) & 0xFF), 
        (uint8_t)(val & 0xFF)
    };

    return writeBytes(temp, 4);
}

