#include "ByteSequence.h"

#ifndef REGISTERCONTROLLER_H
#define REGISTERCONTROLLER_H

class RegisterController {
    private:
        int latchPin;
        int clockPin;
        int dataPin;
        int oePin;
        int clearPin;
        ByteSequence seq;
        int numPins;

    public:
        void RegisterController(int latchPin, int clockPin, int dataPin, int oePin, int clearPin, ByteSequence seq);
        void ResgisterController(int latchPin, int clockPin, int dataPin, int oePin, int clearPin, int numPins);
        ~RegisterController();
        void updateRegisters();
}


#endif // REGISTERCONTROLLER_H