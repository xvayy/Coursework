#include "RealNumber.h"
#include <cmath>
#include <stdexcept>

RealNumber::RealNumber()
	: Number(0.0), minRange(0.0), maxRange(1.0) {}


RealNumber::RealNumber(double val, double min, double max)
    : Number(val), minRange(min), maxRange(max) {
}

RealNumber::RealNumber(const RealNumber& other)
    : Number(), minRange(other.minRange), maxRange(other.maxRange) {
    value = other.value;
}

RealNumber::RealNumber(RealNumber&& other) noexcept
    : Number(), minRange(other.minRange), maxRange(other.maxRange) {
    value = other.value;
    other.value = 0;
    other.minRange = 0;
    other.maxRange = 0;
}

RealNumber::~RealNumber() {
	//cout << "\nDestructor called for RealNumber with value: " << value << endl;
}

bool RealNumber::isInRange(double val) const {
    return val >= minRange && val <= maxRange;
}

void RealNumber::print() const {
    cout << "Real number value: " <<  value;
	cout << ", Range: [" << minRange << ", " << maxRange << "]";
}

// Геттери і сеттери

void RealNumber::setValue(double val) {
    if (!isInRange(val)) {
        throw out_of_range("Value out of range");
    }
    value = val;
}

double RealNumber::getValue() const {
	return value;
}

double RealNumber::getMaxRange() const {
	return maxRange;
}

void RealNumber::setMaxRange(double max) {
	if (max < minRange) {
		throw invalid_argument("Max range cannot be less than min range");
	}
	maxRange = max;
}

double RealNumber::getMinRange() const {
	return minRange;
}

void RealNumber::setMinRange(double min) {
	if (min > maxRange) {
		throw invalid_argument("Min range cannot be greater than max range");
	}
	minRange = min;
}

// Оператори перевантаження
RealNumber RealNumber::operator+(const RealNumber& other) const {
    double result = value + other.value;
    double newMin = min(minRange, other.minRange);
    double newMax = max(maxRange, other.maxRange);

    if (result < newMin) newMin = result;
    if (result > newMax) newMax = result;

    return RealNumber(result, newMin, newMax);
}

RealNumber RealNumber::operator-(const RealNumber& other) const {
    double result = value - other.value;
    double newMin = min(minRange, other.minRange);
    double newMax = max(maxRange, other.maxRange);

    if (result < newMin) newMin = result;
    if (result > newMax) newMax = result;

    return RealNumber(result, newMin, newMax);
}

RealNumber RealNumber::operator*(const RealNumber& other) const {
    double result = value * other.value;

    // всі можливі комбінації меж для добутку
    double possibleBounds[] = {
        minRange * other.minRange,
        minRange * other.maxRange,
        maxRange * other.minRange,
        maxRange * other.maxRange
    };

    double newMin = *min_element(begin(possibleBounds), end(possibleBounds));
    double newMax = *max_element(begin(possibleBounds), end(possibleBounds));

    if (result < newMin) newMin = result;
    if (result > newMax) newMax = result;

    return RealNumber(result, newMin, newMax);
}

RealNumber RealNumber::operator/(const RealNumber& other) const {
    if (other.value == 0) {
        throw runtime_error("Division by zero");
    }

    if (other.minRange <= 0 && other.maxRange >= 0) {
        throw runtime_error("Division range includes zero");
    }

    double result = value / other.value;

    double possibleBounds[] = {
        minRange / other.minRange,
        minRange / other.maxRange,
        maxRange / other.minRange,
        maxRange / other.maxRange
    };
    double newMin = *min_element(begin(possibleBounds), end(possibleBounds));
    double newMax = *max_element(begin(possibleBounds), end(possibleBounds));

    if (result < newMin) newMin = result;
    if (result > newMax) newMax = result;

    return RealNumber(result, newMin, newMax);
}

double RealNumber::operator()() const {
    return value - floor(value); // Дробова частина
}

int RealNumber::operator[](int index) const {
    if (index != 0) {
        throw invalid_argument("Index must be 0 for integer part");
    }
    return static_cast<int>(floor(value)); // Ціла частина
}

RealNumber& RealNumber::operator=(const RealNumber& other) {
    if (this != &other) {
        value = other.value;
        minRange = other.minRange;
        maxRange = other.maxRange;
    }
    return *this;
}

RealNumber& RealNumber::operator=(RealNumber&& other) noexcept {
    if (this != &other) {
        value = other.value;
        minRange = other.minRange;
        maxRange = other.maxRange;
        other.value = 0;
        other.minRange = 0;
        other.maxRange = 0;
    }
    return *this;
}

ostream& operator<<(ostream& os, const RealNumber& rn) {
    os << rn.value;
    return os;
}

istream& operator>>(istream& is, RealNumber& rn) {
    double val;
    double min;
    double max;
    cout << "(val, min, max):\n";
    is >> val;
    is >> min;
	is >> max;
	rn.setMinRange(min); 
	rn.setMaxRange(max); 
    rn.setValue(val);
    return is;
}