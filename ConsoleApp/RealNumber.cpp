#include "RealNumber.h"
#include <cmath>
#include <stdexcept>

RealNumber::RealNumber(double val, double min, double max)
    : value(val), minRange(min), maxRange(max) {
    if (!isInRange(val)) {
        throw std::invalid_argument("Value out of range!");
    }
}

RealNumber::RealNumber(const RealNumber& other)
    : value(other.value), minRange(other.minRange), maxRange(other.maxRange) {
}

RealNumber::RealNumber(RealNumber&& other) noexcept
    : value(other.value), minRange(other.minRange), maxRange(other.maxRange) {
    other.value = 0.0;
}

RealNumber::~RealNumber() {}

bool RealNumber::isInRange(double val) const {
    return val >= minRange && val <= maxRange;
}

void RealNumber::setValue(double val) {
    if (!isInRange(val)) {
        throw std::invalid_argument("Value out of range!");
    }
    value = val;
}

double RealNumber::getValue() const {
    return value;
}

RealNumber RealNumber::operator+(const RealNumber& other) const {
    double result = value + other.value;
    return RealNumber(result, minRange, maxRange);
}

RealNumber RealNumber::operator-(const RealNumber& other) const {
    double result = value - other.value;
    return RealNumber(result, minRange, maxRange);
}

RealNumber RealNumber::operator*(const RealNumber& other) const {
    double result = value * other.value;
    return RealNumber(result, minRange, maxRange);
}

RealNumber RealNumber::operator/(const RealNumber& other) const {
    if (other.value == 0) {
        throw std::invalid_argument("Division by zero!");
    }
    double result = value / other.value;
    return RealNumber(result, minRange, maxRange);
}

double RealNumber::operator()() const {
    return value - floor(value);
}

double RealNumber::operator[](int) const {
    return floor(value);
}

RealNumber& RealNumber::operator=(const RealNumber& other) {
    if (this != &other) {
        value = other.value;
    }
    return *this;
}

RealNumber& RealNumber::operator=(RealNumber&& other) noexcept {
    if (this != &other) {
        value = other.value;
        other.value = 0.0;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const RealNumber& num) {
    os << num.value;
    return os;
}

std::istream& operator>>(std::istream& is, RealNumber& num) {
    double val;
    is >> val;
    num.setValue(val);
    return is;
}

void RealNumber::display() const {
    std::cout << "Value: " << value << std::endl;
}