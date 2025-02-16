#include "ByteSequence.h"
#include <stdint.h>
#include <Arduino.h>
using namespace std;

#define BYTESIZE 8

void reWriteByte(int position, uint8_t newByte, ByteSequence *seq) {
	if (position >= seq->numBytes) {
		return;
	}
	seq->bytes[position] = newByte;
}

ByteSequence *newSequence(int numBytes) {
	ByteSequence *seq = new ByteSequence;

	seq->bytes = new uint8_t[numBytes];
	// init to zero
	for (int i = 0; i < numBytes; i++) {
		seq->bytes[i] = 0;
	}
	seq->numBytes = numBytes;

	return seq;
}

void rightShiftBits(ByteSequence *seq) {
	uint8_t carry = 0;
	for (int i = seq->numBytes - 1; i >= 0; i--) {
		uint8_t temp = seq->bytes[i] & 0x01;
		seq->bytes[i] >>= 1;
		if (carry != 0x00) {
		seq->bytes[i] |= 0x80;
		}

		carry = temp;
	}
}

void leftShiftBits(ByteSequence *seq) {
	bool carry = false;
	for (int i = 0; i < seq->numBytes; i++) {
		uint8_t temp = seq->bytes[i] & 0x80;
		seq->bytes[i] <<= 1;
		if (carry) {
			seq->bytes[i] |= 0x01;
		}

		carry = (temp != 0x00);
	}
}

void freeSequence(ByteSequence *seq) {
	delete seq->bytes;
	delete seq;
}

void convertNumtoSequence(ByteSequence *seq, int num) {
	uint32_t u_num = num;
	for (int i = 0; i < seq->numBytes; i++) {
		uint32_t mask = 0x000000FF;
		seq->bytes[i] = 0x00;	// reset byte
		seq->bytes[i] = u_num & 0x000000FF;
		u_num >>= 8;
	}

}

void displayState(ByteSequence *seq) {
	Serial.print("Number of Bytes: ");
	Serial.println(seq->numBytes);


	for (int i = 0; i < seq->numBytes; i++) {
		Serial.print(byteToString(seq->bytes[i]));
		Serial.print("\n");
	}
}

String byteToString(uint8_t byte) {
	String str = "";
	for (int i = 0; i < BYTESIZE; i++) {
		if ((byte & (0x80 >> i)) != 0x00) {
			str += "1";
		} else {
			str += "0";
		}
	}
	str += "\0";
	return str;
}


/**
 * iterator pattern
 */
Iterator *newIterator(ByteSequence *seq) {
	Iterator *it = new Iterator;
	it->pos = 0;
	it->seq = seq;
	return it;
}

/**
 * returns the current element of a sequence and iterates to the next element
 * returns END if no other element exists
 */
int next(Iterator *it) {

	if (it->pos >= it->seq->numBytes * 8) {
		return END;
	}

	// Reverse direction of bytes
	// int byte = it->seq->numBytes - (it->pos / 8) - 1;
	// uint8_t mask = 0x80 >> (it->pos % 8);

	// normal direction of bytes
	int byte = it->pos / 8;
	uint8_t mask = 0x01 << (it->pos % 8);
	it->pos++;
	return (it->seq->bytes[byte] & mask) != 0x00;

}

void freeIterator(Iterator *it) {
	delete it;
}


