#include <BufferInputStream.h>

BufferInputStream::BufferInputStream(const uint8_t* buffer, size_t len) {
    _buffer = Buffer((uint8_t*)buffer, len);
}

int BufferInputStream::available() {
    return _buffer.available();
}

int BufferInputStream::read() {
    int res = _buffer.get();
    _buffer++;

    return res;
}

int BufferInputStream::peek() {
    return _buffer.get();
}

size_t BufferInputStream::write(uint8_t w) {
    return 0;
}

int BufferInputStream::read(uint8_t& val) {
    uint8_t temp[1] = {0};
    int res = readBytes(temp, 1); 
    if (res == 1) {
        val = temp[0];
    }

    return res;
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
