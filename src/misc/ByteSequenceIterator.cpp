#include <iostream>
#include "Iterator.h"
#include "../ByteSequence.h"

Iterator::Iterator(ByteSequence seq) {
    this.seq = seq;
    pos = 0;
}

Iterator::~Iterator(){}

int Iterator::next() {
    if (pos >= seq->numBytes * 8) {
        return NULL;
    }

    // Reverse direction of bytes
    // int byte = seq->numBytes - (pos / 8) - 1;
    // uint8_t mask = 0x80 >> (pos % 8);

    // normal direction of bytes
    int byte = pos / 8;
    uint8_t mask = 0x01 << (pos % 8);
    pos++;
    return (seq->bytes[byte] & mask) != 0x00;
}

bool Iterator::atEnd() {
    if (pos >= seq->numBytes) {
        return true;
    }

    return false;
}