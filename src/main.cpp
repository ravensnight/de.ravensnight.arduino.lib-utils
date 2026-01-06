#include <Arduino.h>

#include <utils/Buffer.h>
#include <Logger.h>
#include <SerialLogAdapter.h>

using namespace ravensnight::utils;
using namespace ravensnight::logging;

const char* text = "Hello world.";
Buffer b((uint8_t*)text, 0, strlen(text));

uint8_t len = 0, i = 0;

Ref<Buffer> ref(RefType::weak);
Ref<const char> ref2(RefType::weak);

SerialLogAdapter logAdapter;

namespace ravensnight::logging {
    LogLevel getLogLevel(const char* category) {
        return LogLevel::trace;
    }
}

void setup() {

    Logger::setup(&logAdapter);

    len = strlen(text);
    i = 0;
    ref = &b;
    ref2.set(text);

    Logger::root.debug("Initialized.");
}

void loop() {
    if (i >= len) i = 0;

    uint8_t elem = (*ref).bytes()[i];
    Logger::root.debug("Using (*ref).bytes[i] - char at pos %d is %d", i, elem);

    elem = ref->bytes()[i];
    Logger::root.debug("Using ref->bytes[i] - Char at pos %d is %d", i, elem);

    elem = ref2[i];
    Logger::root.debug("Using ref2[i] -  Char at pos %d is %d", i, elem);

    i++;

    delay(1000);
}