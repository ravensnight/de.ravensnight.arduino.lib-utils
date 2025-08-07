#ifndef __StreamHelper_h__
#define __StreamHelper_h__

#include <Arduino.h>
#include <Stream.h>

namespace ravensnight::utils {

    class StreamHelper {

        public:

            static void read8(const uint8_t* buffer, uint8_t& val);
            static void read16(const uint8_t* buffer, uint16_t& val);
            static void read32(const uint8_t* buffer, uint32_t& val) ;
            static void read64(const uint8_t* buffer, uint64_t& val) ;

            static void write8(uint8_t* buffer, uint8_t val);
            static void write16(uint8_t* buffer, uint16_t val);
            static void write32(uint8_t* buffer, uint32_t val);
            static void write64(uint8_t* buffer, uint64_t val);
    };
}

Stream& operator >>(Stream& is, uint8_t &val);
Stream& operator >>(Stream& is, uint16_t &val);
Stream& operator >>(Stream& is, uint32_t &val);
Stream& operator >>(Stream& is, uint64_t &val);
Stream& operator >>(Stream& is, bool val);

Stream& operator <<(Stream& os, uint8_t val);
Stream& operator <<(Stream& os, uint16_t val);
Stream& operator <<(Stream& os, uint32_t val);
Stream& operator <<(Stream& os, uint64_t val);
Stream& operator <<(Stream& os, bool val);
Stream& operator <<(Stream& os, const char* val);

#endif // __StreamHelper_h__