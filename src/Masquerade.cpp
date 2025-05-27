#include <Masquerade.h>
#include <Logger.h>

using namespace LOGGING;

Masquerade::Masquerade() {
    _mask = 0xFF;
}

Masquerade::Masquerade(uint8_t mask) {
    _mask = mask;
}

size_t Masquerade::getEncodedSize(size_t sourceLen) {
    return sourceLen;
}

size_t Masquerade::getDecodedSize(size_t sourceLen) {
    return sourceLen;
}

size_t Masquerade::encode(Stream& out, Stream& in) {
    size_t res = 0;
    uint8_t val = 0;

    while ((in.available() > 0) && (out.availableForWrite() > 0)) {
        in >> val;
        out << val;
        res++;
    }

    return res;
}

size_t Masquerade::decode(Stream& out, Stream& in) {
    size_t res = 0;
    uint8_t val = 0;

    while ((in.available() > 0) && (out.availableForWrite() > 0)) {
        in >> val;
        out << val;
        res++;
    }

    return res;
}
