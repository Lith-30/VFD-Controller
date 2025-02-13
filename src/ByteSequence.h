
#ifndef BYTESEQUENCE_H
#define BYTESEQUENCE_H

#define END 2;

struct ByteSequence {
  uint8_t *bytes;
  int numBytes;
};

struct Iterator {
  ByteSequence *seq;
  int pos;
};

void reWriteByte(int position, uint8_t newByte, ByteSequence *seq);
void LeftShiftBits(ByteSequence *seq);
void freeSequence(ByteSequence *seq);
Iterator *newIterator(ByteSequence *seq);
int next(Iterator *it);
void freeIterator(Iterator *it);
ByteSequence *newSequence(int numBytes);

#endif // BYTESEQUENCE_H




