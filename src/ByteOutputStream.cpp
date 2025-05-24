#include <ByteOutputStream.h>

ByteOutputStream::ByteOutputStream(uint8_t *buffer, size_t size) {
    _buffer = buffer;
    _size = size;
    _pos = 0;
}

int ByteOutputStream::available() {
    return (_size - _pos);
}

int ByteOutputStream::read() {
    return -1;
}

int ByteOutputStream::peek() {
    return -1;
}

int ByteOutputStream::availableForWrite() {
    return available();
}

size_t ByteOutputStream::write(uint8_t w) {
    if (_pos < _size) {
        _buffer[_pos] = w;
        _pos++;
    }

    return _pos;
}

size_t ByteOutputStream::writeBytes(const uint8_t* buffer, size_t size) {
    size_t avl = (size_t)availableForWrite();
    if (size > avl) {
        return -1;
    }

    for (size_t i = 0; i < size; i++) {
        write(buffer[i]);
    }

    return size;
}

int ByteOutputStream::write(uint16_t val) {
    uint8_t* buffer = (uint8_t*)&val;
    return writeBytes(buffer, 2);
}

int ByteOutputStream::write(uint32_t val) {
    uint8_t* buffer = (uint8_t*)&val;
    return writeBytes(buffer, 4);
}

ByteOutputStream& ByteOutputStream::operator<<(uint8_t val) {
    write(val);
    return *this;
}

ByteOutputStream& ByteOutputStream::operator<<(uint16_t val) {
    write(val);    
    return *this;
}

ByteOutputStream& ByteOutputStream::operator<<(uint32_t val) {
    write(val);    
    return *this;
}

