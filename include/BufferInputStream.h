#ifndef __BufferInputStream_H__
#define __BufferInputStream_H__

#include <Arduino.h>
#include <Stream.h>
#include <Buffer.h>

class BufferInputStream : public Stream {

    private:

        Buffer _buffer;

    public:

        BufferInputStream(const uint8_t* buffer, size_t len);

        int read(uint8_t& val);
        int read(uint16_t& val);
        int read(uint32_t& val);

        int available();
        int peek();
        int read();
        
        size_t write(uint8_t w);
};

#endif //  __BufferInputStream_H__