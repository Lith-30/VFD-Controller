#include <iostream>

#ifndef ITERATOR_H
#define ITERATOR_H

class Iterator {
public:
    Iterator();
    ~Iterator();
    int next();
    bool atEnd();
};

#endif // ITERATOR_H