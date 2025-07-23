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

    public:
        RegisterController(int latchPin, int clockPin, int dataPin, int oePin, int clearPin);
        ~RegisterController();
        void updateRegisters(ByteSequence seq);
        int getLatchPin();
        int getClockPin();
        int getDataPin();
        int getOePin();
        int getClearPin(); 
};


#endif // REGISTERCONTROLLER_H