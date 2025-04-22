#include "DigitalScale.h"

DigitalScale::DigitalScale(double weight, double error, double price, double min, double max)
    : RealNumber(weight, min, max), errorMargin(error), unitPrice(price) {
    totalPrice = calculateTotalPrice();
}

DigitalScale::DigitalScale(const DigitalScale& other)
    : RealNumber(other), errorMargin(other.errorMargin), unitPrice(other.unitPrice), totalPrice(other.totalPrice) {
}

DigitalScale::DigitalScale(DigitalScale&& other) noexcept
    : RealNumber(std::move(other)), errorMargin(other.errorMargin), unitPrice(other.unitPrice), totalPrice(other.totalPrice) {
    other.errorMargin = 0.0;
    other.unitPrice = 0.0;
    other.totalPrice = 0.0;
}

DigitalScale::~DigitalScale() {}

double DigitalScale::getWeight() const {
    return value;
}

double DigitalScale::getErrorMargin() const {
    return errorMargin;
}

double DigitalScale::calculateTotalPrice() const {
    return value * unitPrice;
}

DigitalScale& DigitalScale::operator=(const DigitalScale& other) {
    if (this != &other) {
        RealNumber::operator=(other); // Викликаємо operator= базового класу
        errorMargin = other.errorMargin;
        unitPrice = other.unitPrice;
        totalPrice = other.totalPrice;
    }
    return *this;
}

DigitalScale& DigitalScale::operator=(DigitalScale&& other) noexcept {
    if (this != &other) {
        RealNumber::operator=(std::move(other)); // Викликаємо operator= переміщення базового класу
        errorMargin = other.errorMargin;
        unitPrice = other.unitPrice;
        totalPrice = other.totalPrice;
        other.errorMargin = 0.0;
        other.unitPrice = 0.0;
        other.totalPrice = 0.0;
    }
    return *this;
}

void DigitalScale::display() const {
    std::cout << "Weight: " << value << " kg, Total Price: " << calculateTotalPrice() << " (Error: " << errorMargin << " kg)" << std::endl;
}