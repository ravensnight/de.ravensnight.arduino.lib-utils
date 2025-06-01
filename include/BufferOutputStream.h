#ifndef __BufferOutputStream_H__
#define __BufferOutputStream_H__

#include <Arduino.h>
#include <Stream.h>
#include <Buffer.h>

namespace ravensnight::utils {
class BufferOutputStream : public Stream {

    private:

        Buffer _buffer;
        size_t _pos;

    public:

        BufferOutputStream(uint8_t* buffer, size_t len);
        BufferOutputStream(Buffer& target);

        int write(uint16_t val);
        int write(uint32_t val);

        int available();
        int peek();
        int read();
        
        int availableForWrite();

        size_t write(uint8_t w);
        size_t writeBytes(const uint8_t* buffer, size_t len);
};

}

#endif // __BufferOutputStream_H__