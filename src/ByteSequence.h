#include <stdint.h>
#include <Arduino.h>

#ifndef BYTESEQUENCE_H
#define BYTESEQUENCE_H

#define END 2

struct ByteSequence {
  uint8_t *bytes;
  int numBytes;
};

struct Iterator {
  ByteSequence *seq;
  int pos;
};

void reWriteByte(int position, uint8_t newByte, ByteSequence *seq);
void leftShiftBits(ByteSequence *seq);
void rightShiftBits(ByteSequence *seq);
void freeSequence(ByteSequence *seq);
Iterator *newIterator(ByteSequence *seq);
int next(Iterator *it);
void freeIterator(Iterator *it);
ByteSequence *newSequence(int numBytes);
void convertNumtoSequence(ByteSequence *seq, int num);
void convertNumtoSequence(int num);
String byteToString(uint8_t byte);
void displayState(ByteSequence *seq);

#endif // BYTESEQUENCE_H




