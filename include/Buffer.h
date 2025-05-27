#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <Arduino.h>
#include <StreamOperators.h>

class Buffer {

    private:

        uint8_t* _buffer;   // the buffer itself
        size_t _size;        // the size if the buffer
        bool _mine;         // the buffer is my own buffer. I will delete it.
        size_t _pos;        // current position;

    protected:

        bool set(size_t pos, uint8_t val);
        int get(size_t pos) const;

    public:

        Buffer();
        Buffer(size_t len);
        ~Buffer();

        Buffer& wrap(uint8_t* buffer, size_t len);
        Buffer& create(size_t len);

        void destroy();
        
        size_t available();         // number of bytes available behind pos

        size_t size() const;
        size_t pos() const;         // get the current position 
        Buffer& pos(size_t pos);    // set a new position

        int get();                  // get data at current position
        bool set(uint8_t val);      // set data at current position
        bool add(const uint8_t* buffer, size_t amount); // add multiple bytes to buffer. move pos.

        uint8_t* bytes();

        Buffer& operator ++(int val);    // increment the position pointer
        Buffer& operator --(int val);    // decrement the position pointer        

        int operator[] (size_t pos) const;    // get data at given absolute position.

        friend Stream& operator <<(Stream& os, const Buffer& buffer);
        friend Stream& operator >>(Stream& is, Buffer& buffer);  
    
};


#endif // __BUFFER_H__