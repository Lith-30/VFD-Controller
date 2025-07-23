#include "ByteSequenceIterator.h"
#include "../ByteSequence.h"
#define BYTESIZE 8


ByteSequenceIterator::ByteSequenceIterator(ByteSequence sequence):
    seq(sequence),
    pos(0)
{
}

ByteSequenceIterator::~ByteSequenceIterator(){}

int ByteSequenceIterator::next() {
    if (pos >= seq.getNumBytes() * BYTESIZE) {
        return 0;
    }

    // Reverse direction of bytes
    // int byte = seq->numBytes - (pos / BYTESIZE) - 1;
    // uintBYTESIZE_t mask = 0xBYTESIZE0 >> (pos % BYTESIZE);

    // normal direction of bytes
    int byte = pos / BYTESIZE;
    uint8_t mask = 0x01 << (pos % BYTESIZE);
    pos++;
    return (seq.getByte(byte) & mask) != 0x00;
}

bool ByteSequenceIterator::atEnd() {
    if (pos >= seq.getNumBytes() * BYTESIZE) {
        return true;
    }

    return false;
}