#include <StreamHelper.h>
#include <Stream.h>
#include <Logger.h>

using namespace ravensnight::logging;
using namespace ravensnight::utils;

Stream& operator >>(Stream& is, uint8_t &val) {    
    int i = is.read();
    if (i > -1) {
        val = i & 0xFF;
    }

    return is;
}

Stream& operator >>(Stream& is, uint16_t &val) {
    uint8_t buf[2];
    if (is.readBytes(buf, 2) == 2) {
        StreamHelper::read16(buf, val);
    }
    return is;
}

Stream& operator >>(Stream& is, uint32_t &val) {
    uint8_t buf[4];
    if (is.readBytes(buf, 4) == 4) {
        StreamHelper::read32(buf, val);
    }
    return is;
}

Stream& operator <<(Stream& os, uint8_t val) {
    os.write(val);
    return os;
}

Stream& operator <<(Stream& os, uint16_t val) {
    uint8_t buf[2];
    StreamHelper::write16(buf, val);
    
    os.write(buf[0]);
    os.write(buf[1]);
    return os;
}

Stream& operator <<(Stream& os, uint32_t val) {
    uint8_t buf[4];
    StreamHelper::write32(buf, val);
    
    os.write(buf[0]);
    os.write(buf[1]);
    os.write(buf[2]);
    os.write(buf[3]);
    return os;
}

Stream& operator <<(Stream& os, const char* val) {
    for (size_t i = 0; i < strlen(val); i++) {
        os.write(val[i]);        
    }    
    return os;
}

namespace ravensnight::utils {

void StreamHelper::read8(const uint8_t* buffer, uint8_t& val) {    
    val = buffer[0];
}

void StreamHelper::read16(const uint8_t* buffer, uint16_t& val) {
    val = buffer[1]; val <<= 8;
    val |= buffer[0]; 
}

void StreamHelper::read32(const uint8_t* buffer, uint32_t& val) {
    val = buffer[3]; val <<= 8;
    val |= buffer[2]; val <<= 8;
    val |= buffer[1]; val <<= 8;
    val |= buffer[0]; 
}

void StreamHelper::write8(uint8_t* buffer, uint8_t val) {
    buffer[0] = val & 0xFF;

    //Logger::dump("StreamHelper::write32 - wrote", buffer, 1, 0);
}

void StreamHelper::write16(uint8_t* buffer, uint16_t val) {
    buffer[0] = val & 0xFF;
    buffer[1] = (val >> 8) & 0xFF;

    //Logger::dump("StreamHelper::write32 - wrote", buffer, 2, 0);
}

void StreamHelper::write32(uint8_t* buffer, uint32_t val) {
    buffer[0] = val & 0xFF;
    buffer[1] = (val >> 8) & 0xFF;
    buffer[2] = (val >> 16) & 0xFF;
    buffer[3] = (val >> 24) & 0xFF;

    //Logger::dump("StreamHelper::write32 - wrote", buffer, 4, 0);
}

}