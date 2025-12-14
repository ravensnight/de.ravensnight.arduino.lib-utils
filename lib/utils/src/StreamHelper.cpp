#include <utils/StreamHelper.h>
#include <utils/LoggerConfig.h>

#include <Stream.h>

using namespace ravensnight::logging;
using namespace ravensnight::utils;

Stream& operator >>(Stream& is, bool &val) {    
    int i = is.read();
    if (i > -1) {
        val = ((i & 0xFF) > 0);
    }

    return is;
}

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

Stream& operator >>(Stream& is, uint64_t &val) {
    uint8_t buf[8];
    if (is.readBytes(buf, 8) == 8) {
        StreamHelper::read64(buf, val);
    }

    return is;
}

Stream& operator <<(Stream& os, bool val) {
    os.write(val);
    return os;
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

Stream& operator <<(Stream& os, uint64_t val) {
    uint8_t buf[8];
    StreamHelper::write64(buf, val);
    
    for (uint8_t i = 0; i < 8; i++) os.write(buf[i]);
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

void StreamHelper::read64(const uint8_t* buffer, uint64_t& val) {
    val = 0;
    for (int8_t i = 7; i >= 0; i--) {
        val <<= 8;
        val |= buffer[i]; 
    }
}

void StreamHelper::write8(uint8_t* buffer, uint8_t val) {
    buffer[0] = val & 0xFF;

    _logger.dump("StreamHelper::write32 - wrote", buffer, 1, 0);
}

void StreamHelper::write16(uint8_t* buffer, uint16_t val) {
    buffer[0] = val & 0xFF;
    buffer[1] = (val >> 8) & 0xFF;

    _logger.dump("StreamHelper::write32 - wrote", buffer, 2, 0);
}

void StreamHelper::write32(uint8_t* buffer, uint32_t val) {
    buffer[0] = val & 0xFF;
    buffer[1] = (val >> 8) & 0xFF;
    buffer[2] = (val >> 16) & 0xFF;
    buffer[3] = (val >> 24) & 0xFF;

    _logger.dump("StreamHelper::write32 - wrote", buffer, 4, 0);
}

void StreamHelper::write64(uint8_t* buffer, uint64_t src) {
    uint64_t val = src;
    for (uint8_t i = 0; i < 8; i++) {
        buffer[i] = val & 0xFF;
        val >>= 8;
    }

    _logger.dump("StreamHelper::write64 - wrote", buffer, 4, 0);
}

ClassLogger StreamHelper::_logger(LC_UTILS);

}