#include "PackagingWorkshop.h"

// Реалізація ітератора
ScaleIterator::ScaleIterator(DigitalScale* start, int size, int index)
    : ptr(start), size(size), index(index) {
}

DigitalScale& ScaleIterator::operator*() {
    return ptr[index];
}

ScaleIterator& ScaleIterator::operator++() {
    ++index;
    return *this;
}

bool ScaleIterator::operator!=(const ScaleIterator& other) const {
    return index != other.index;
}

// Реалізація класу PackagingWorkshop
PackagingWorkshop::PackagingWorkshop(double target, int initialCapacity)
    : targetWeight(target), capacity(initialCapacity), count(0) {
    scales = new DigitalScale[capacity];
}

PackagingWorkshop::~PackagingWorkshop() {
    delete[] scales;
}

void PackagingWorkshop::addScale(const DigitalScale& scale) {
    if (count >= capacity) {
        // Розширюємо масив, якщо досягнуто межі
        capacity *= 2;
        DigitalScale* newScales = new DigitalScale[capacity];
        for (int i = 0; i < count; ++i) {
            newScales[i] = scales[i];
        }
        delete[] scales;
        scales = newScales;
    }
    scales[count] = scale;
    ++count;
}

void PackagingWorkshop::packageProduct() {
    double currentWeight = 0.0;
    std::cout << "Packaging process started for target weight: " << targetWeight << " kg" << std::endl;

    for (ScaleIterator it = begin(); it != end(); ++it) {
        DigitalScale& scale = *it;
        if (currentWeight + scale.getWeight() <= targetWeight) {
            currentWeight += scale.getWeight();
            scale.display();
        }
    }

    std::cout << "Total packaged weight: " << currentWeight << " kg" << std::endl;
}

double PackagingWorkshop::calculateTotalError() const {
    double totalError = 0.0;
    for (int i = 0; i < count; ++i) {
        totalError += scales[i].getErrorMargin();
    }
    return totalError;
}

double PackagingWorkshop::calculateTotalPrice() const {
    double totalPrice = 0.0;
    for (int i = 0; i < count; ++i) {
        totalPrice += scales[i].calculateTotalPrice();
    }
    return totalPrice;
}

ScaleIterator PackagingWorkshop::begin() {
    return ScaleIterator(scales, count, 0);
}

ScaleIterator PackagingWorkshop::end() {
    return ScaleIterator(scales, count, count);
}