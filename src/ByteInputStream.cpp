#include <ByteInputStream.h>

ByteInputStream::ByteInputStream(const uint8_t *buffer, size_t size) {
    _buffer = buffer;
    _size = size;
    _pos = 0;
}

int ByteInputStream::available() {
    return (_size - _pos);
}

int ByteInputStream::read() {
    int b = -1;
    if (_pos < _size) {
        b = _buffer[_pos];
        _pos++;
    }

    return b;
}

int ByteInputStream::peek() {
    if (_pos < _size) {
        return _buffer[_pos];
    }

    return -1;
}

size_t ByteInputStream::write(uint8_t w) {
    return 0;
}

int ByteInputStream::read(uint8_t& val) {
    return readBytes((uint8_t*)&val, 1);
}

int ByteInputStream::read(uint16_t& val) {
    return readBytes((uint8_t*)&val, 2);
}

int ByteInputStream::read(uint32_t& val) {
    return readBytes((uint8_t*)&val, 4);
}
