#include <utils/Buffer.h>
#include <utils/LoggerConfig.h>

using namespace ravensnight::logging;

namespace ravensnight::utils
{

    Stream &operator<<(Stream &os, const Buffer &buffer)
    {
        uint8_t *arr = buffer.bytes();
        Logger::trace("Write buffer to output stream. Len: %d", buffer.length());

        for (size_t i = 0; i < buffer.length(); i++)
        {
            os << arr[i];
        }

        return os;
    };

    Stream &operator>>(Stream &is, Buffer &buffer)
    {
        int v = 0;
        while (buffer.avail())
        {
            v = is.read();
            if (v < 0)
                break;

            buffer.append((uint8_t)v);
        }
        return is;
    }

    Buffer::Buffer()
    {
        _start = 0;
        _size = 0;
        _buffer = 0;
        _idx = 0;
        _mine = false;
    }

    Buffer::Buffer(uint8_t *buffer, size_t start, size_t len)
    {
        _start = start;
        _size = len;
        _idx = 0;
        _buffer = buffer;
        _mine = false;
    }

    Buffer::Buffer(size_t len)
    {
        this->_buffer = (uint8_t *)malloc(len);
        this->_idx = 0;
        this->_start = 0;
        this->_size = len;
        this->_mine = true;
    }

    Buffer::~Buffer()
    {
        destroy();
    }

    void Buffer::destroy()
    {
        if ((_mine) && (_buffer != 0))
        {
            _logger.trace("destroy buffer.");
            free(_buffer);
            _buffer = 0;
            _start = 0;
            _size = 0;
            _idx = 0;
            _mine = false;
        }
    }

    void Buffer::reset()
    {
        _idx = _start;
    }

    size_t Buffer::capacity() const
    {
        return _size;
    }

    size_t Buffer::avail() const
    {
        size_t res = _size - _idx;
        _logger.trace("Available for writing to buffer: %d", res);
        return res;
    }

    size_t Buffer::length() const
    {
        return _idx;
    }

    size_t Buffer::moveTo(size_t idx)
    {
        if (idx < _size)
        {
            _idx = idx;
        }
        else
        {
            _idx = _size;
        }

        return _idx;
    }

    size_t Buffer::append(uint8_t val)
    {
        if (avail() < 1)
            return 0;

        StreamHelper::write8(bytesAt(_idx), val);
        _idx++;

        _logger.dump("Buffer::append", bytes(), _idx, 0);
        return _idx;
    }

    size_t Buffer::append(uint16_t val)
    {
        if (avail() < 2)
            return 0;

        StreamHelper::write16(bytesAt(_idx), val);
        _idx += 2;

        _logger.dump("Buffer::append", bytes(), _idx, 0);
        return _idx;
    }

    size_t Buffer::append(uint32_t val)
    {
        if (avail() < 4)
            return 0;

        StreamHelper::write32(bytesAt(_idx), val);
        _idx += 4;

        _logger.dump("Buffer::append", bytes(), _idx, 0);
        return _idx;
    }

    size_t Buffer::append(const uint8_t *source, size_t amount)
    {

        size_t len = avail();
        if (len > amount)
            len = amount;

        if (len > 0)
        {
            memcpy(bytesAt(_idx), source, len);
            _idx += len;
        }

        _logger.dump("Buffer::append", bytes(), _idx, 0);
        return _idx;
    }

    uint8_t *Buffer::bytes() const
    {
        return (_buffer + _start);
    }

    uint8_t *Buffer::bytesAt(size_t pos) const
    {
        return (_buffer + (_start + pos));
    }

    ClassLogger Buffer::_logger(LC_UTILS);

}
