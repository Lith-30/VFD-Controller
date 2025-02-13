#include <Arduino.h>
#include "ByteSequence.h"

void updateRegisters(uint16_t val);
void pong();
void counter();
void clearRegisters();
void allOn();
void setBrightness(int level);

int tDelay = 100;
int latchPin = 11;      // (11) ST_CP [RCK] on 74HC595
int clockPin = 9;      // (9) SH_CP [SCK] on 74HC595
int dataPin = 12;     // (12) DS [S1] on 74HC595
int oePin = 8;
int clearPin = 7;

void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  pinMode(oePin, OUTPUT);
  pinMode(clearPin, OUTPUT);
  digitalWrite(clearPin, HIGH);
  setBrightness(100);
  //Serial.begin(9600);
}

void loop() 
{
  counter();
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

void allOn() {
  digitalWrite(latchPin, LOW);
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

void counter() {
  uint16_t count = 0;

  for (int i = 0; (count & 0xFFFF) != 0xFFFF; i++) {
    updateRegisters(count);
    count++;
  }
}

void pong() {
  uint16_t ball = 0x0001;

  for (int i = 0; i < 16; i++) {
    updateRegisters(ball);
    ball <<= 1;
    delay(50);
  }

  ball = 0x8000;
  for (int i = 0; i < 16; i++) {
    updateRegisters(ball);
    ball >>= 1;
    delay(50);
  }

}