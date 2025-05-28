#include <Buffer.h>
#include <Logger.h>

using namespace LOGGING;

Stream& operator <<(Stream& os, const Buffer& buffer) {
    int v = 0;
    for (size_t i = 0; i < buffer.length(); i++) {
        v = buffer.get(i);
        if (v < 0) break;

        os << (uint8_t)v;
    }

    return os;
};

Stream& operator >>(Stream& is, Buffer& buffer) {

    int v = 0;
    for (size_t i = 0; i < buffer.length(); i++) {        
        v = is.read();
        if (v < 0) break;

        if (buffer.set(i, (uint8_t)v) < 1) {
            break;
        }
    }

    return is;    
}

uint8_t& Buffer::operator[] (size_t pos) {
    if (pos < _length) {
        return _buffer[pos];
    } else {
        Logger::error("Read from invalid index %d (max=%d)!", pos, _length);
        _nil = 0;
        return _nil;
    }    
}

Buffer::Buffer() {
    _length = 0;
    _buffer = 0;
    _mine = false;
}

Buffer::Buffer(uint8_t* buffer, size_t len) {
    _length = len;
    _buffer = buffer;
    _mine = false;
}

Buffer::Buffer(size_t len) {
    this->_buffer = (uint8_t*)malloc(len);
    this->_length = len;
    this->_mine = true;
}

Buffer::~Buffer() {
    destroy();
}

void Buffer::destroy() {
    if ((_mine) && (_buffer != 0)) {
        free(_buffer);
        _buffer = 0;
        _length = 0;
    }
}

size_t Buffer::length() const {
    return _length;
}

int Buffer::get(size_t pos) const {
    if (pos < _length) {
        return _buffer[pos];
    }    

    return -1;
}

size_t Buffer::get(size_t pos, uint8_t* target, size_t amount) const {
    size_t len = _length - pos;
    if (len > amount) len = amount;

    memcpy(target, (_buffer + pos), len);
    return len;
}

size_t Buffer::get(size_t pos, Buffer& buffer) const {
    return get(pos, buffer.bytes(), buffer.length());
}

size_t Buffer::set(size_t pos, uint8_t val) {
    if (pos < _length) {
        _buffer[pos] = val;
        return 1;
    }
    return 0;
}

size_t Buffer::set(size_t pos, const uint8_t* source, size_t amount) {
    size_t len = _length - pos;
    if (len > amount) len = amount;

    memcpy((_buffer + pos), source, len);
    return len;
}

size_t Buffer::set(size_t pos, Buffer& buffer) {
    return set(pos, buffer.bytes(), buffer.length());
}

uint8_t* Buffer::bytes() {
    return _buffer;
}
