#include "ByteSequence.h"
#include <stdint.h>
using namespace std;


void reWriteByte(int position, uint8_t newByte, ByteSequence *seq) {
	if (position >= seq->numBytes) {
		return;
	}
	seq->bytes[position] = newByte;
}

ByteSequence *newSequence(int length) {
	ByteSequence *seq = new ByteSequence;

	seq->bytes = new uint8_t[length];
	seq->numBytes = length;

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

/**
 * returns the current element of a sequence and iterates to the next element
 * return 2 if no other element exists
 */
int next(Iterator *it) {

	if (it->pos >= it->seq->numBytes) {
		return 2;
	}

	uint8_t mask = 0xF0 >> (it->pos % 8);
	it->pos++;
	return (it->seq->bytes[it->pos / 8] & mask) != 0x00;

}

void freeIterator(Iterator *it) {
	delete it;
}


