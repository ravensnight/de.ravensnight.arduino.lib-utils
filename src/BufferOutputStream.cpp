#include <utils/BufferOutputStream.h>

namespace ravensnight::utils {

BufferOutputStream::BufferOutputStream(size_t capacity) : _buffer(capacity) {
}

BufferOutputStream::BufferOutputStream(uint8_t* buffer, size_t len) : _buffer(buffer, 0, len) {
}

BufferOutputStream::~BufferOutputStream() {
    _buffer.destroy();
}

int BufferOutputStream::available() {
    return 0;
}

int BufferOutputStream::read() {
    return -1;
}

int BufferOutputStream::peek() {
    return -1;
}

int BufferOutputStream::availableForWrite() {
    return _buffer.avail();
}

size_t BufferOutputStream::write(uint8_t w) {
    return _buffer.append(w);
}

size_t BufferOutputStream::writeBytes(const uint8_t* buffer, size_t size) {
    return _buffer.append(buffer, size);
}

Buffer& BufferOutputStream::buffer() {
    return _buffer;
}

}