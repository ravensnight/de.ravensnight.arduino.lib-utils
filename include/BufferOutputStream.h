#ifndef __BufferOutputStream_H__
#define __BufferOutputStream_H__

#include <Arduino.h>
#include <Stream.h>
#include <Buffer.h>

namespace ravensnight::utils {
class BufferOutputStream : public Stream {

    private:

        Buffer _buffer;

    public:

        BufferOutputStream(size_t capacity);
        BufferOutputStream(uint8_t* buffer, size_t len);
        ~BufferOutputStream();

        int available();
        int peek();
        int read();
        
        int availableForWrite();

        Buffer& buffer();

        size_t write(uint8_t w);
        size_t writeBytes(const uint8_t* buffer, size_t len);
};

}

#endif // __BufferOutputStream_H__