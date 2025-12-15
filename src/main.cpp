#include <Arduino.h>

#include <utils/Buffer.h>
#include <Logger.h>

using namespace ravensnight::utils;
using namespace ravensnight::logging;

const char* text = "Hello world.";
Buffer b((uint8_t*)text, 0, strlen(text));

uint8_t len = 0, i = 0;

Ref<Buffer> ref(RefType::weak);

void setup() {
    len = strlen(text);
    i = 0;
    ref = &b;
}

void loop() {
    if (i >= len) i = 0;

    uint8_t elem = (*ref).bytes()[i];
    Logger::debug("Char at pos %d is %d", i, elem);

    elem = ref[i];
    Logger::debug("Char at pos %d is %d", i, elem);

    i++;

    delay(1000);
}