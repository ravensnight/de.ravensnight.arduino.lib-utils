#include <Buffer.h>

Stream& operator <<(Stream& os, const Buffer& buffer) {
    int v = 0;
    for (size_t i = 0; i < buffer.size(); i++) {
        v = buffer[i];
        if (v < 0) break;

        os << (uint8_t)v;
    }

    return os;
};

Stream& operator >>(Stream& is, Buffer& buffer) {

    int v = 0;
    for (size_t i = 0; i < buffer.size(); i++) {        
        v = is.read();
        if (v < 0) break;

        buffer.set(i, (uint8_t)v);
    }

    return is;    
}

int Buffer::operator[] (size_t pos) const {
    return get(pos);
}

Buffer& Buffer::operator++ (int val) {
    if (_pos < _size) {
        _pos++;
    }
    
    val = _pos;
    return (*this);
}

Buffer& Buffer::operator-- (int val) {
    if (_pos > 0){
        _pos--;
    } 
    
    val = _pos;
    return (*this);
}

Buffer::Buffer() {
    _size = 0;
    _buffer = 0;
    _mine = false;
    _pos = 0;
}

Buffer::Buffer(size_t len) {
    create(len);
}

Buffer::~Buffer() {
    destroy();
}

Buffer& Buffer::wrap(uint8_t* buffer, size_t len) {
    destroy();

    this->_buffer = buffer;
    this->_size = len;
    this->_mine = false;

    return (*this);
}

Buffer& Buffer::create(size_t len) {
    destroy();

    this->_buffer = (uint8_t*)malloc(len);
    this->_size = len;
    this->_mine = true;

    return (*this);
}

size_t Buffer::available() {
    if (_buffer == 0) return 0;
    return (_size - _pos);
}

void Buffer::destroy() {
    if ((_mine) && (_buffer != 0)) {
        free(_buffer);
        _buffer = 0;
        _size = 0;
    }
}

size_t Buffer::size() const {
    return _size;
}

size_t Buffer::pos() const {
    return _pos;
}

Buffer& Buffer::pos(size_t p) {
    _pos = 0;
    return (*this);
}

int Buffer::get() {
    int res = get(_pos);
    if (res < 0) {
        return -1;
    }

    _pos++;
    return res;
}

int Buffer::get(size_t pos) const {
    if (pos < _size) {
        return (*this)[_pos];
    }    
    return -1;
}

bool Buffer::set(size_t pos, uint8_t val) {
    if (pos < _size) {
        _buffer[pos] = val;
        return true;
    }

    return false;
}

bool Buffer::set(uint8_t val) {
    return set(_pos, val);
}

bool Buffer::add(const uint8_t* source, size_t amount) {
    if (available() < amount) return false;
    memcpy(_buffer, source, amount);
    _pos += amount;
    return true;
}

uint8_t* Buffer::bytes() {
    return _buffer;
}

