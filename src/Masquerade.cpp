#include <Masquerade.h>
#include <Logger.h>

using namespace ravensnight::logging;

namespace ravensnight::utils {

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

size_t Masquerade::encode(Stream& out, const uint8_t* buffer, size_t len) {    
    size_t size = out.availableForWrite();
    if (size > len) size = len;

    for (size_t i = 0; i < size; i++) {
        out.write(buffer[i]);
    }    
    return size;
}

size_t Masquerade::decode(Stream& out, const uint8_t* buffer, size_t len) {
    return encode(out, buffer, len);
}

}