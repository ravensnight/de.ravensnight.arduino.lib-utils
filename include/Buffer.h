#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <Arduino.h>
#include <StreamOperators.h>

class Buffer {

    private:

        uint8_t  _nil = 0;      // the nil buffer element for invalid indices
        uint8_t* _buffer;       // the buffer itself
        size_t   _length;       // the size if the buffer
        bool     _mine;         // the buffer is my own buffer. I will delete it.

    public:

        Buffer();
        Buffer(size_t len);
        Buffer(uint8_t* buffer, size_t len);
        ~Buffer();

        void destroy();        
        size_t length() const;
        uint8_t* bytes();

        /**
         * Set a single byte to given position.
         * @return 1, if successful or 0 if position was invalid.
         */
        size_t set(size_t pos, uint8_t val);

        /**
         * Assign multiple bytes.
         * @param pos the position to start with copy
         * @param buffer the buffer to copy from
         * @param amount the number of bytes to copy from buffer
         * 
         * @return the number of bytes copied (maximum is size - pos);
         */
        size_t set(size_t pos, const uint8_t* buffer, size_t amount); // add multiple bytes to buffer
        size_t set(size_t pos, Buffer& buffer); // add multiple bytes to buffer

        /**
         * Get a single byte from buffer.
         * @return the byte value (0..255) or -1, if pos was invalid.
         */
        int get(size_t pos) const;

        /**
         * Read a number of bytes from buffer
         * @param pos the position to get data from
         * @param buffer the buffer to write in
         * @param amount the number of bytes requested (max is size - pos)
         * 
         * @return the number of bytes assigned
         */
        size_t get(size_t pos, uint8_t* buffer, size_t amount) const;   // read multiple bytes from buffer
        size_t get(size_t pos, Buffer& buffer) const;   // read multiple bytes from buffer

        uint8_t& operator[] (size_t pos);    // get data at given absolute position.

        friend Stream& operator <<(Stream& os, const Buffer& buffer);
        friend Stream& operator >>(Stream& is, Buffer& buffer);
    
};


#endif // __BUFFER_H__