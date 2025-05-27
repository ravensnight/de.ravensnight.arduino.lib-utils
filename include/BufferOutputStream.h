#ifndef __BufferOutputStream_H__
#define __BufferOutputStream_H__

#include <Arduino.h>
#include <Stream.h>
#include <Buffer.h>

class BufferOutputStream : public Stream {

    private:

        Buffer _buffer;

    public:

        BufferOutputStream(uint8_t* buffer, size_t len);

        int write(uint16_t val);
        int write(uint32_t val);

        int available();
        int peek();
        int read();
        
        int availableForWrite();

        size_t write(uint8_t w);
        size_t writeBytes(const uint8_t* buffer, size_t len);
};

#endif // __BufferOutputStream_H__