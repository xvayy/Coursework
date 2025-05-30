#pragma once
#include "DigitalScale.h"

class DigitalScaleIterator {
private:
    DigitalScale* ptr;
public:
    DigitalScaleIterator(DigitalScale* p);
    DigitalScale& operator*();
    DigitalScale* operator->();
    DigitalScaleIterator& operator++();
    bool operator!=(const DigitalScaleIterator& other) const;
};
