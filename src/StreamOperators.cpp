#include <Stream.h>

Stream& operator >>(Stream& is, uint8_t &val) {
    if (is.available() >= 1) {
        is.readBytes((uint8_t*)&val, 1);
    }
    return is;
}

Stream& operator >>(Stream& is, uint16_t &val) {
    if (is.available() >= 2) {
        is.readBytes((uint8_t*)&val, 2);
    }
    return is;
}

Stream& operator >>(Stream& is, uint32_t &val) {
    if (is.available() >= 4) {
        is.readBytes((uint8_t*)&val, 4);
    }
    return is;
}

Stream& operator <<(Stream& os, uint8_t val) {
    if (os.availableForWrite() >= 1) {
        os.write(val);
    }
    return os;
}

Stream& operator <<(Stream& os, uint16_t val) {

    if (os.availableForWrite() >= 2) {
        os.write((val >> 8) & 0xFF);
        os.write(val & 0xFF);
    }
    return os;

}

Stream& operator <<(Stream& os, uint32_t val) {

    if (os.availableForWrite() >= 4) {
        os.write((val >> 24) & 0xFF);
        os.write((val >> 16) & 0xFF);
        os.write((val >> 8) & 0xFF);
        os.write(val & 0xFF);
    }

    return os;
}
