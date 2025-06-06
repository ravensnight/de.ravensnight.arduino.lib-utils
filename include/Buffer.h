#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <Arduino.h>
#include <StreamHelper.h>

namespace ravensnight::utils {
class Buffer {

    private:

        uint8_t* _buffer;       // the buffer itself
        size_t   _start;        // start inside the buffer
        size_t   _size;         // the size if the buffer
        size_t   _idx;          // current position
        bool     _mine;         // the buffer is my own buffer. I will delete it.

    public:

        Buffer();
        Buffer(size_t capacity);
        Buffer(uint8_t* buffer, size_t start, size_t size);
        ~Buffer();

        /**
         * Destroy the internal buffer
         */
        void destroy();        

        /**
         * Set position pointer to 0
         */
        void reset();

        /**
         * Return the number of bytes available until size is reached.
         */
        size_t avail() const;

        /**
         * Return the capacity of the buffer
         */
        size_t capacity() const;

        /**
         * The number of bytes already written. Equals the current pos for writing.
         */
        size_t length() const;

        /**
         * Set the position pointer
         */
        size_t moveTo(size_t pos);

        /**
         * Return the byte buffer
         */
        uint8_t* bytes() const;

        /**
         * Return the byte buffer at a given position
         */
        uint8_t* bytesAt(size_t start) const;
        
        /**
         * Append a single byte to current position
         * @return 1, if successful or 0 if position was invalid.
         */
        size_t append(uint8_t val);

        size_t append(uint16_t val);

        size_t append(uint32_t val);

        /**
         * Assign multiple bytes.
         * @param pos the position to start with copy
         * @param buffer the buffer to copy from
         * @param amount the number of bytes to copy from buffer
         * 
         * @return the number of bytes copied (maximum is size - pos);
         */
        size_t append(const uint8_t* buffer, size_t amount); // add multiple bytes to buffer

        friend Stream& operator <<(Stream& os, const Buffer& buffer);
        friend Stream& operator >>(Stream& is, Buffer& buffer);
   
};

}

#endif // __BUFFER_H__