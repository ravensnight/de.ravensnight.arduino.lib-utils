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
    Buffer in((uint8_t*)buffer, len);
    out << in;
    return len;
}

size_t Masquerade::decode(Stream& out, const uint8_t* buffer, size_t len) {
    Buffer in((uint8_t*)buffer, len);
    out << in;
    return len;
}

}