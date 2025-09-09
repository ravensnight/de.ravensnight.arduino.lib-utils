#ifndef __BASE128_H__
#define __BASE128_H__

#include <Arduino.h>
#include <ClassLogger.h>
#include <utils/Converter.h>
#include <utils/Buffer.h>

using namespace ravensnight::logging;

namespace ravensnight::utils {
class Base128 : public Converter {

    private:

        static ClassLogger _logger;

    public:

    Base128();

    /**
     * Enccode some given inBytes to outBytes.
     */
    size_t encode(Stream& os, const uint8_t* buffer, size_t len);

    /**
     * Decode some given inBytes to outBytes.
     */
    size_t decode(Stream& os, const uint8_t* buffer, size_t len);

    /**
     * Get the size of the encoded stream from given source
     */
    size_t getEncodedSize(size_t decodedLen);

    /**
     * Get the size of the decoded stream from given source
     */
    size_t getDecodedSize(size_t encodedLen);
};

}
#endif // __BASE128_H__