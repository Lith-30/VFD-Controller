#include <Arduino.h>
#include "ByteSequence.h"
#include "RegisterController.h"

#define BYTESIZE 8

void updateRegisters(uint16_t val);
void pong(RegisterController reg);
void counter(RegisterController reg);
void clearRegisters();
void allOn();
void setBrightness(int level);
void alternating(RegisterController reg);
void demo(RegisterController reg);

int tDelay = 100;
int latchPin = 11;      // (11) ST_CP [RCK] on 74HC595
int clockPin = 9;      // (9) SH_CP [SCK] on 74HC595
int dataPin = 12;     // (12) DS [S1] on 74HC595
int oePin = 8;
int clearPin = 7;

int numBytes = 8;
// init for 48 pins or 6 bytes
ByteSequence seq(numBytes);
RegisterController reg(latchPin, clockPin, dataPin, oePin, clearPin);

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  pinMode(oePin, OUTPUT);
  pinMode(clearPin, OUTPUT);
  digitalWrite(clearPin, HIGH);
  setBrightness(0);
  
  

    Serial.begin(9600);
}



void loop() {
  // Grid Pin
  seq.reWriteByte(3, 0x10);
  // Segment Pin
  seq.reWriteByte(0, 0x01);
  reg.updateRegisters(seq);
  // for (int i = 0; i < reg->seq->numBytes; i++) {
  //   reWriteByte(i, 0xFF, reg->seq);
  // }
  // updateRegisters(reg);
  
  // for (int i = 0; i < reg->seq->numBytes; i++) {
  //   reWriteByte(i, 0xFF, reg->seq);
  // }
  // updateRegisters(reg);
  // delay(1000);
  // for (int i = 0; i < reg->seq->numBytes; i++) {
  //   reWriteByte(i, 0xFF, reg->seq);
  // }
  // updateRegisters(reg);
  // delay(1000);
  
  // counter(reg);
  
}

void demo(RegisterController reg) {
  
  
  for (int i = 0; i < 3; i++) {
    pong(reg);
  }
  delay(400);

  for (int i = 0; i < 1; i++) {
    counter(reg);
  }
  delay(400);
  for (int i = 0; i < 8; i++) {
    alternating(reg);
  }
  delay(400);
  
}

void alternating(RegisterController reg) {
  int numBytes = seq.getNumBytes();
  for (int i = 0; i < numBytes; i++) {
    seq.reWriteByte(i, 0xAA);
  }
  reg.updateRegisters(seq);
  delay(300);

  for (int i = 0; i < numBytes; i++) {
    seq.reWriteByte(i, 0x55);
  }
  reg.updateRegisters(seq);
  delay(300);

}

/**
  Brightness can go from 0 to 1023
  Scale is inverted, higher the number, lower the brightness
*/
void setBrightness(int level) {
  if (level > 1023 || level < 0) {
    return;
  }

  analogWrite(oePin, level);
}

void counter(RegisterController reg) {
  int count = 0;

  for (int i = 0; count < 0xFF; i++) {
    seq.convertNumtoSequence(count);
    for (int j = 1; j < seq.getNumBytes(); j++) {
      seq.reWriteByte(j, seq.getByte(0));
    }
    // displayState(reg->seq);
    reg.updateRegisters(seq);
    delay(100);
    count++;
  }
}

void pong(RegisterController reg) {
  seq.reWriteByte(0, 0xC1);
  
  for (int i = 0; i < seq.getNumBytes() * BYTESIZE; i++) {
    reg.updateRegisters(seq);
    seq.leftShiftBits();
    Serial.println(i);
    // displayState(reg->seq);
    
    delay(50);
  }

  seq.reWriteByte(5, 0x83);
  for (int i = 0; i < seq.getNumBytes() * BYTESIZE; i++) {
    reg.updateRegisters(seq);
    seq.rightShiftBits();
    // displayState(reg->seq);
    delay(50);
  }

}