#ifndef __BYTESTREAM_H__
#define  __BYTESTREAM_H__

#include <Arduino.h>
#include <Stream.h>

class ByteStream : public Stream {

    private:

        uint8_t* _buffer;
        size_t _pos = 0;
        size_t _size = 0;

    public:

        ByteStream(uint8_t *buffer, size_t size);

        int read(uint8_t& val);
        int read(uint16_t& val);
        int read(uint32_t& val);

        int write(uint16_t val);
        int write(uint32_t val);

        int available();
        int peek();
        int read();
        
        int availableForWrite();

        size_t write(uint8_t w);
        size_t writeBytes(const uint8_t* buffer, size_t len);

        ByteStream& operator<<(uint8_t val);
        ByteStream& operator<<(uint16_t val);
        ByteStream& operator<<(uint32_t val);

        ByteStream& operator>>(uint8_t& val);
        ByteStream& operator>>(uint16_t& val);
        ByteStream& operator>>(uint32_t& val);
};

#endif //  __BYTESTREAM_H__