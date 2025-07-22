#ifndef BYTESEQUENCE_H
#define BYTESEQUENCE_H

#include <stdint.h>
#include <Arduino.h>

#define END 2

// struct ByteSequence {
//   uint8_t *bytes;
//   int numBytes;
// };

class ByteSequence {
  private:
    uint8_t *bytes;
    int numBytes;

  public:
    ByteSequence(int numBytes);
    ~ByteSequence();
    int getNumBytes();
    void reWriteByte(int position, uint8_t newByte);
    void leftShiftBits();
    void rightShiftBits();
    void freeSequence();
    ByteSequence *newSequence(int numBytes);
    void convertNumtoSequence(int num);
    String byteToString(uint8_t byte);
    void displayState();

};



#endif // BYTESEQUENCE_H




