#ifndef __BYTEINPUTSTREAM_H__
#define __BYTEINPUTSTREAM_H__

#include <Arduino.h>
#include <Stream.h>

class ByteInputStream : public Stream {

    private:

        const uint8_t* _buffer;
        size_t _pos = 0;
        size_t _size = 0;

    public:

        ByteInputStream(const uint8_t *buffer, size_t size);

        int read(uint8_t& val);
        int read(uint16_t& val);
        int read(uint32_t& val);

        int available();
        int peek();
        int read();
        
        size_t write(uint8_t w);

        ByteInputStream& operator>>(uint8_t& val);
        ByteInputStream& operator>>(uint16_t& val);
        ByteInputStream& operator>>(uint32_t& val);

};

#endif //  __BYTEINPUTSTREAM_H__