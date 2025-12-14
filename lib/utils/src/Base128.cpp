#include <utils/LoggerConfig.h>
#include <utils/Base128.h>

using namespace ravensnight::logging;
namespace ravensnight::utils {


Base128::Base128() {
    // do nothing
}

size_t Base128::getDecodedSize(size_t encodedLen) {
    size_t res = encodedLen * 7 / 8;
    return res;
}

size_t Base128::decode(Stream& target, const uint8_t* buffer, size_t len) {
    int outSize = getDecodedSize(len);
    if (outSize > target.availableForWrite()) {
        _logger.error("Decoded size does not match size of outstream: %d <> %d", outSize, target.availableForWrite());
        return 0;
    }

    uint8_t out = 0, in = 0, bit = 0;
    size_t count = 0;

    for (size_t i = 0; i < len; i++) {
        in = buffer[i];

        for (int i = 0; i < 7; i++) {
            out <<= 1;

            int match = (1 << (6 - i));
            if ((in & match) > 0) {
                out |= 0x1;
            }

            bit++;
            if (bit == 8) {
                _logger.trace("decode - write out: %x", out);
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

size_t Base128::encode(Stream& target, const uint8_t* buffer, size_t len) {
    int outSize = getDecodedSize(len);
    if (outSize > target.availableForWrite()) return 0;

    uint8_t out = 0, bit = 0, in = 0; 
    size_t count = 0;

    for (size_t i = 0; i < len; i++) {
        in = buffer[i];

        _logger.trace("encode - source: %x", in);
        for (int i = 0; i < 8; i++) {
            out <<= 1;
            int match = (1 << (7 - i));
            if ((in & match) > 0) {
                out |= 0x1;
            }

            bit++;
            if (bit == 7) {
                _logger.trace("encode - write out: %x", out);
                target << out;
                count++;

                bit = 0;
                out = 0;                 
            }
        }
    }

    if (bit > 0) {
        out <<= (7 - bit);
        _logger.trace("encode - write out: %x", out);
        target << out;
        count++;
    }

    return count;    
}

ClassLogger Base128::_logger(LC_UTILS);

}