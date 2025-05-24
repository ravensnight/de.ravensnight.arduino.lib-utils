#ifndef __BYTEOUTPUTSTREAM_H__
#define __BYTEOUTPUTSTREAM_H__

#include <Arduino.h>
#include <Stream.h>

class ByteOutputStream : public Stream {

    private:

        uint8_t* _buffer;
        size_t _pos = 0;
        size_t _size = 0;

    public:

        ByteOutputStream(uint8_t *buffer, size_t size);

        int write(uint16_t val);
        int write(uint32_t val);

        int available();
        int peek();
        int read();
        
        int availableForWrite();

        size_t write(uint8_t w);
        size_t writeBytes(const uint8_t* buffer, size_t len);
};

#endif // __BYTEOUTPUTSTREAM_H__