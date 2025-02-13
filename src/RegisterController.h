#ifndef REGISTERCONTROLLER_H
#define REGISTERCONTROLLER_H

struct RegController {
    ByteSequence *seq;
    int latchPin;
    int clockPin;
    int dataPin;
    int oePin;
    int clearPin;
    int numPins;
};

RegController *newController(int latchPin, int clockPin, int dataPin, int oePin, int clearPin, ByteSequence *seq);
RegController *newController(int latchPin, int clockPin, int dataPin, int oePin, int clearPin, int numPins);
void updateRegisters(RegController *con);

#endif // REGISTERCONTROLLER_H