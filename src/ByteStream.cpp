#include <ByteStream.h>

ByteStream::ByteStream(uint8_t *buffer, size_t size) {
    _buffer = buffer;
    _size = size;
    _pos = 0;
}

int ByteStream::available() {
    return (_size - _pos);
}

int ByteStream::read() {
    int b = -1;
    if (_pos < _size) {
        b = _buffer[_pos];
        _pos++;
    }

    return b;
}

int ByteStream::peek() {
    if (_pos < _size) {
        return _buffer[_pos];
    }

    return -1;
}

int ByteStream::availableForWrite() {
    return available();
}

size_t ByteStream::write(uint8_t w) {
    if (_pos < _size) {
        _buffer[_pos] = w;
        _pos++;
    }

    return _pos;
}

size_t ByteStream::writeBytes(const uint8_t* buffer, size_t size) {
    size_t avl = (size_t)availableForWrite();
    if (size > avl) {
        return -1;
    }

    for (size_t i = 0; i < size; i++) {
        write(buffer[i]);
    }

    return size;
}

int ByteStream::read(uint8_t& val) {
    return readBytes((uint8_t*)&val, 1);
}

int ByteStream::read(uint16_t& val) {
    return readBytes((uint8_t*)&val, 2);
}

int ByteStream::read(uint32_t& val) {
    return readBytes((uint8_t*)&val, 4);
}

int ByteStream::write(uint16_t val) {
    uint8_t* buffer = (uint8_t*)&val;
    return writeBytes(buffer, 2);
}

int ByteStream::write(uint32_t val) {
    uint8_t* buffer = (uint8_t*)&val;
    return writeBytes(buffer, 4);
}

ByteStream& ByteStream::operator>>(uint8_t& val) {
    read(val);
    return *this;
}

ByteStream& ByteStream::operator>>(uint16_t& val) {
    read(val);    
    return *this;
}

ByteStream& ByteStream::operator>>(uint32_t& val) {
    read(val);    
    return *this;
}

ByteStream& ByteStream::operator<<(uint8_t val) {
    write(val);
    return *this;
}

ByteStream& ByteStream::operator<<(uint16_t val) {
    write(val);    
    return *this;
}

ByteStream& ByteStream::operator<<(uint32_t val) {
    write(val);    
    return *this;
}

