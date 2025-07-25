#include "RegisterController.h"
#include <Arduino.h>
#include "ByteSequence.h"
#include "misc/ByteSequenceIterator"

#define BYTESIZE 8;

// RegController *newController(int latchPin, int clockPin, int dataPin, int oePin, int clearPin, ByteSequence *seq) {
//     RegController *con = new RegController;

//     con->latchPin = latchPin;
//     con->clockPin = clockPin;
//     con->dataPin = dataPin;
//     con->oePin = oePin;
//     con->clearPin = clearPin;
//     con->seq = seq;
//     con->numPins = seq->numBytes * BYTESIZE;

//     return con;
// }

// RegController *newController(int latchPin, int clockPin, int dataPin, int oePin, int clearPin, int numPins) {
//     RegController *con = new RegController;

//     con->latchPin = latchPin;
//     con->clockPin = clockPin;
//     con->dataPin = dataPin;
//     con->oePin = oePin;
//     con->clearPin = clearPin;
//     con->seq = newSequence((numPins + 7) / 8);
//     con->numPins = numPins;

//     return con;
// }

// void updateRegisters(RegController *con) {
//     Iterator *iter = newIterator(con->seq);
//     int val = next(iter);

//     digitalWrite(con->latchPin, LOW);
//     //PORTD &= ~(1 << con->latchPin);

//     while (val != END) {
//         digitalWrite(con->clockPin, LOW);

//         //digitalWrite(con->dataPin, val ? HIGH : LOW);

//         if (val) {
//             digitalWrite(con->dataPin, HIGH);
//         } else {
//             digitalWrite(con->dataPin, LOW);
//         }
        
//         digitalWrite(con->clockPin, HIGH);
//         val = next(iter);
//     }
//     digitalWrite(con->clockPin, LOW);
//     digitalWrite(con->latchPin, HIGH);

//     freeIterator(iter);
//   }

RegisterController(int latchPin, int clockPin, int dataPin, int oePin, int clearPin, ByteSequence seq) {
    latchPin = latchPin;
    clockPin = clockPin;
    dataPin = dataPin;
    oePin = oePin;
    clearPin = clearPin;
    seq = seq;
    numPins = seq.getNumBytes() * BYTESIZE;
}

RegisterController(int latchPin, int clockPin, int dataPin, int oePin, int clearPin) {
    ByteSequence seq((numPins + 7) / 8);

    RegisterController(latchPin, clockPin, dataPin, oePin, clearPin, seq);
}

~RegisterController() {}


void updateRegisters() {
    ByteSequenceIterator iter(seq);

    int val = iter.next();

    digitalWrite(latchPin, LOW);
    //PORTD &= ~(1 << latchPin);

    while (!iter.atEnd()) {
        digitalWrite(clockPin, LOW);

        //digitalWrite(dataPin, val ? HIGH : LOW);

        if (val) {
            digitalWrite(dataPin, HIGH);
        } else {
            digitalWrite(dataPin, LOW);
        }
        
        digitalWrite(clockPin, HIGH);
        val = iter.next();
    }
    digitalWrite(clockPin, LOW);
    digitalWrite(latchPin, HIGH);

    
}

