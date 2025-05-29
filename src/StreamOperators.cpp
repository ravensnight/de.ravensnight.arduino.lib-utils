#include <Stream.h>
#include <Logger.h>

using namespace LOGGING;

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
        val = (buf[1] << 8) | (buf[0]);
    }
    return is;
}

Stream& operator >>(Stream& is, uint32_t &val) {
    uint8_t buf[4];
    if (is.readBytes(buf, 4) == 4) {
        val = (buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0];
    }
    return is;
}

Stream& operator <<(Stream& os, uint8_t val) {
    os.write(val);
    return os;
}

Stream& operator <<(Stream& os, uint16_t val) {
    os << (uint8_t)(val & 0xFF);
    os << (uint8_t)((val >> 8) & 0xFF);
    return os;

}

Stream& operator <<(Stream& os, uint32_t val) {
    os << (uint8_t)(val & 0xFF);
    os << (uint8_t)((val >> 8) & 0xFF);
    os << (uint8_t)((val >> 16) & 0xFF);
    os << (uint8_t)((val >> 24) & 0xFF);
    return os;
}
