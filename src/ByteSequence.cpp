#include "ByteSequence.h"
#include <stdint.h>
using namespace std;


void reWriteByte(int position, uint8_t newByte, ByteSequence *seq) {
	if (position >= seq->numBytes) {
		return;
	}
	seq->bytes[position] = newByte;
}

ByteSequence *newSequence(int numBytes) {
	ByteSequence *seq = new ByteSequence;

	seq->bytes = new uint8_t[numBytes];
	seq->numBytes = numBytes;

	return seq;
}

void LeftShiftBits(ByteSequence *seq) {
	uint8_t carry = 0;
	for (int i = 0; i < seq->numBytes; i++) {
		seq->bytes[i] >>= 1;
		if (carry != 0x00) {
		seq->bytes[i] |= 0x10;
		}

		uint8_t carry = seq->bytes[i] & 0x01;
	}
}

void freeSequence(ByteSequence *seq) {
	delete seq->bytes;
	delete seq;
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

void convertNumtoSequence(ByteSequence *seq, int num) {

}

ByteSequence *convertNumtoSequence(int num) {
	ByteSequence *seq = newSequence(log(num) / log(2) * BYTESIZE);
}

/**
 * returns the current element of a sequence and iterates to the next element
 * returns END if no other element exists
 */
int next(Iterator *it) {

	if (it->pos >= it->seq->numBytes) {
		return END;
	}

	uint8_t mask = 0xF0 >> (it->pos % 8);
	it->pos++;
	return (it->seq->bytes[it->pos / 8] & mask) != 0x00;

}

void freeIterator(Iterator *it) {
	delete it;
}


