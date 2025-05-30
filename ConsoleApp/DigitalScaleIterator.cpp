#include "DigitalScaleIterator.h"

DigitalScaleIterator::DigitalScaleIterator(DigitalScale* p) : ptr(p) {}
DigitalScale& DigitalScaleIterator::operator*() { return *ptr; }
DigitalScale* DigitalScaleIterator::operator->() { return ptr; }
DigitalScaleIterator& DigitalScaleIterator::operator++() { ++ptr; return *this; }
bool DigitalScaleIterator::operator!=(const DigitalScaleIterator& other) const { return ptr != other.ptr; }
