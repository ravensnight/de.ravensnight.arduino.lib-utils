#include <utils/BufferInputStream.h>

namespace ravensnight::utils {

BufferInputStream::BufferInputStream(const uint8_t* buffer, size_t len) {
    _buffer.attach((uint8_t*)buffer);
    _size = len;
    _pos = 0;
}

BufferInputStream::BufferInputStream(Buffer& buffer) {
    _buffer = buffer.bytes();
    _size = buffer.length();
    _pos = 0;
}

int BufferInputStream::available() {
    return (_size - _pos);
}

int BufferInputStream::read() {
    int res = -1;
    if (_pos < _size) {
        res = _buffer.get()[_pos];
        _pos++;
    }

    return res;
}

int BufferInputStream::peek() {
    if (_pos < _size) {
        return _buffer.get()[_pos];
    }

    return -1;
}

size_t BufferInputStream::write(uint8_t w) {
    return 0;
}

}