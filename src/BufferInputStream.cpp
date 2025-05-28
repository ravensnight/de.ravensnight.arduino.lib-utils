#include <BufferInputStream.h>

BufferInputStream::BufferInputStream(const uint8_t* buffer, size_t len) {
    _buffer = Buffer((uint8_t*)buffer, len);
    _pos = 0;
}

BufferInputStream::BufferInputStream(Buffer& buffer) {
    _buffer = Buffer(buffer.bytes(), buffer.length());
    _pos = 0;
}

int BufferInputStream::available() {
    return (_buffer.length() - _pos);
}

int BufferInputStream::read() {
    int res = _buffer.get(_pos);
    if (res >= 0) {
        _pos++;
    }
    return res;
}

int BufferInputStream::peek() {
    return _buffer.get(_pos);
}

size_t BufferInputStream::write(uint8_t w) {
    return 0;
}

int BufferInputStream::read(uint8_t& val) {
    int res = read();
    if (res >= 0) {
        val = res;
        return 1;
    }
    return -1;
}

int BufferInputStream::read(uint16_t& val) {
    uint8_t temp[2] = {0};
    int res = readBytes(temp, 2); 

    if (res == 2) {        
        val = temp[0];
        val <<= 8;
        val |= temp[1];
    }

    return res;
}

int BufferInputStream::read(uint32_t& val) {
    uint8_t temp[4] = {0};
    int res = readBytes(temp, 4); 

    if (res == 4) {
        val = 0;    
        for (int i = 0; i < 4; i++) {
            val <<= 8;
            val |= temp[i];
        }
    }

    return res;
}
