#ifndef __CONVERTER_H__
#define __CONVERTER_H__

#include <Arduino.h>
#include <Buffer.h>

namespace ravensnight::utils {
class Converter {

    public:

    /**
     * Enccode some given inBytes to outBytes.
     */
    virtual size_t encode(Stream& os, const uint8_t* buffer, size_t len) = 0;

    /**
     * Decode some given inBytes to outBytes.
     */
    virtual size_t decode(Stream& os, const uint8_t* buffer, size_t len) = 0;

    /**
     * Get the size of the encoded stream from given source
     */
    virtual size_t getEncodedSize(size_t decodedLen) = 0;

    /**
     * Get the size of the decoded stream from given source
     */
    virtual size_t getDecodedSize(size_t encodedLen) = 0;
        
};

}

#endif