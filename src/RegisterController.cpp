#include "RegisterController.h"
#include <Arduino.h>
#include "ByteSequence.h"

#define BYTESIZE 8;

RegController *newController(int latchPin, int clockPin, int dataPin, int oePin, int clearPin, ByteSequence *seq) {
    RegController *con = new RegController;

    con->latchPin = latchPin;
    con->clockPin = clockPin;
    con->dataPin = dataPin;
    con->oePin = oePin;
    con->clearPin = clearPin;
    con->seq = seq;
    con->numPins = seq->numBytes * BYTESIZE;

    return con;
}

RegController *newController(int latchPin, int clockPin, int dataPin, int oePin, int clearPin, int numPins) {
    RegController *con = new RegController;

    con->latchPin = latchPin;
    con->clockPin = clockPin;
    con->dataPin = dataPin;
    con->oePin = oePin;
    con->clearPin = clearPin;
    con->seq = newSequence((numPins + 7) / 8);
    con->numPins = numPins;

    return con;
}

void updateRegisters(RegController *con) {
    Iterator *iter = newIterator(con->seq);
    int val = next(iter);

    digitalWrite(con->latchPin, LOW);

    while (val != END) {
        digitalWrite(con->clockPin, LOW);
        if (val) {
            digitalWrite(con->dataPin, HIGH);
        } else {
            digitalWrite(con->dataPin, LOW);
        }
        digitalWrite(con->clockPin, HIGH);
        Serial.print(val);
        val = next(iter);
    }
    Serial.print("\n");
    digitalWrite(con->clockPin, LOW);
    digitalWrite(con->latchPin, HIGH);

    freeIterator(iter);
  }