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
    void reWriteByte(int position, uint8_t newByte);
    void reWriteByte(int position, uint8_t newByte, ByteSequence seq);
    void leftShiftBits();
    void rightShiftBits();
    void convertNumtoSequence(int num);
    String byteToString(uint8_t byte);
    void displayState();
    uint8_t getByte(int pos);
    int getNumBytes();

};



#endif // BYTESEQUENCE_H




