#ifndef __BufferInputStream_H__
#define __BufferInputStream_H__

#include <Arduino.h>
#include <Stream.h>
#include <utils/Buffer.h>

namespace ravensnight::utils {

class BufferInputStream : public Stream {

    private:

        const uint8_t* _buffer;
        size_t _size;
        size_t _pos;

    public:

        BufferInputStream(const uint8_t* buffer, size_t len);
        BufferInputStream(Buffer& source);

        int available();
        int peek();
        int read();
        
        size_t write(uint8_t w);
};

}

#endif //  __BufferInputStream_H__