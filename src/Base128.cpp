#include <Base128.h>
#include <Logger.h>

using namespace ravensnight::logging;
namespace ravensnight::utils {


Base128::Base128() {
    // do nothing
}

size_t Base128::getDecodedSize(size_t encodedLen) {
    size_t res = encodedLen * 7 / 8;
    return res;
}

size_t Base128::decode(Stream& target, Buffer& source) {
    int outSize = getDecodedSize(source.length());
    if (outSize > target.availableForWrite()) return 0;

    uint8_t out = 0, in = 0, bit = 0;
    size_t count = 0;

    for (size_t i = 0; i < source.length(); i++) {
        in = source[i];

        for (int i = 0; i < 7; i++) {
            out <<= 1;

            int match = (1 << (6 - i));
            if ((in & match) > 0) {
                out |= 0x1;
            }

            bit++;
            if (bit == 8) {
                //Logger::debug("decode - write out: %x", out);
                target << out;
                bit = 0;
                out = 0;        

                count++;                            
            }
        }
    }

    return count;
}

size_t Base128::getEncodedSize(size_t decodedLen) {
    size_t res = decodedLen * 8 / 7;
    if ((decodedLen * 8) % 7 > 0) {
        res++;
    }
    return res;
}

size_t Base128::encode(Stream& target, Buffer& source) {
    int outSize = getDecodedSize(source.length());
    if (outSize > target.availableForWrite()) return 0;

    uint8_t out = 0, bit = 0, in = 0; 
    size_t count = 0;

    for (size_t i = 0; i < source.length(); i++) {
        in = source[i];

        //Logger::debug("encode - source: %x", in);
        for (int i = 0; i < 8; i++) {
            out <<= 1;
            int match = (1 << (7 - i));
            if ((in & match) > 0) {
                out |= 0x1;
            }

            bit++;
            if (bit == 7) {
                //Logger::debug("encode - write out: %x", out);
                target << out;
                count++;

                bit = 0;
                out = 0;                 
            }
        }
    }

    if (bit > 0) {
        out <<= (7 - bit);
        //Logger::debug("encode - write out: %x", out);
        target << out;
        count++;
    }

    return count;

}

}