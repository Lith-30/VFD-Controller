#include <Arduino.h>
#include "ByteSequence.h"
#include "RegisterController.h"

void updateRegisters(uint16_t val);
void pong(RegController *reg);
void counter(RegController *reg);
void clearRegisters();
void allOn();
void setBrightness(int level);
void alternating(RegController *reg);
void demo(RegController *reg);

int tDelay = 100;
int latchPin = 11;      // (11) ST_CP [RCK] on 74HC595
int clockPin = 9;      // (9) SH_CP [SCK] on 74HC595
int dataPin = 12;     // (12) DS [S1] on 74HC595
int oePin = 8;
int clearPin = 7;

int numBytes = 6;
// init for 48 pins or 6 bytes
ByteSequence *seq;
RegController *reg;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  pinMode(oePin, OUTPUT);
  pinMode(clearPin, OUTPUT);
  digitalWrite(clearPin, HIGH);
  setBrightness(100);
  seq = newSequence(numBytes);

  reg = newController(latchPin, clockPin, dataPin, oePin, clearPin, seq);
  
  

  //Serial.begin(9600);
}



void loop() 
{

  demo(reg);
  
}

void demo(RegController *reg) {
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

void alternating(RegController *reg) {
  for (int i = 0; i < reg->seq->numBytes; i++) {
    reWriteByte(i, 0xAA, reg->seq);
  }
  updateRegisters(reg);
  delay(300);

  for (int i = 0; i < reg->seq->numBytes; i++) {
    reWriteByte(i, 0x55, reg->seq);
  }
  updateRegisters(reg);
  delay(300);

}

/**
  Brightness can go from 0 to 1023
*/
void setBrightness(int level) {
  if (level > 1023 || level < 0) {
    return;
  }

  analogWrite(oePin, level);
}

void allOn(RegController *controller) {
  digitalWrite(controller->latchPin, LOW);
  for (int i = 0; i < 48; i++) {
    digitalWrite(clockPin, LOW);
    digitalWrite(dataPin, HIGH);
    digitalWrite(clockPin, HIGH);
  }
  digitalWrite(clockPin, LOW);
  digitalWrite(latchPin, HIGH);
}

void updateRegisters(uint16_t val) {
  digitalWrite(latchPin, LOW);
  
  for (int i = 0; i < 16; i++) {
    digitalWrite(clockPin, LOW);

    if (val & 0x01) {
      digitalWrite(dataPin, HIGH);
    } else {
      digitalWrite(dataPin, LOW);
    }
    digitalWrite(clockPin, HIGH);
    
    val >>= 1;
  }
  digitalWrite(clockPin, LOW);
  digitalWrite(latchPin, HIGH);
}

void clearRegisters() {
  digitalWrite(clearPin, LOW);
  delay(1);
  digitalWrite(clearPin, HIGH);
}

void counter(RegController *reg) {
  int count = 0;

  for (int i = 0; count < 0xFF; i++) {
    convertNumtoSequence(reg->seq, count);
    for (int j = 1; j < reg->seq->numBytes; j++) {
      reWriteByte(j, reg->seq->bytes[0], reg->seq);
    }
    // displayState(reg->seq);
    updateRegisters(reg);
    delay(100);
    count++;
  }
}

void pong(RegController *reg) {
  reWriteByte(0, 0x01, reg->seq);
  
  for (int i = 0; i < reg->numPins; i++) {
    updateRegisters(reg);
    leftShiftBits(reg->seq);
    displayState(reg->seq);
    
    delay(50);
  }

  reWriteByte(5, 0x80, reg->seq);
  for (int i = 0; i < reg->numPins; i++) {
    updateRegisters(reg);
    rightShiftBits(reg->seq);
    displayState(reg->seq);
    delay(50);
  }

}