#ifndef BYTESEQUENCEITERATOR_H
#define BYTESEQUENCEITERATOR_H

#include "Iterator.h"
#include "../ByteSequence.h"


class ByteSequenceIterator : public Iterator {
    private:
        ByteSequence seq;
        int pos;
    
    public:
        ByteSequenceIterator(ByteSequence sequence);
        ~ByteSequenceIterator();
        int next();
        bool atEnd();
        
};

#endif //BYTESEQUENCEITERATOR_H