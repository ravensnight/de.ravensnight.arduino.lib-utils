#include <BufferOutputStream.h>

BufferOutputStream::BufferOutputStream(uint8_t* buffer, size_t len) {
    _buffer = Buffer(buffer, len);
}

int BufferOutputStream::available() {
    return _buffer.available();
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
    _buffer.set(w);
    _buffer++;

    return _buffer.pos();
}

size_t BufferOutputStream::writeBytes(const uint8_t* buffer, size_t size) {
    size_t avl = (size_t)availableForWrite();
    if (size > avl) {
        return -1;
    }

    for (size_t i = 0; i < size; i++) {
        write(buffer[i]);
    }

    return size;
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

