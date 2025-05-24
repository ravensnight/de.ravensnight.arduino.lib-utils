#ifndef __STREAM_OPERATORS_H__
#define __STREAM_OPERATORS_H__

#include <Stream.h>

Stream& operator >>(Stream& is, uint8_t &val);
Stream& operator >>(Stream& is, uint16_t &val);
Stream& operator >>(Stream& is, uint32_t &val);

Stream& operator <<(Stream& os, uint8_t val);
Stream& operator <<(Stream& os, uint16_t val);
Stream& operator <<(Stream& os, uint32_t val);

#endif // #define __STREAM_OPERATORS_H__
