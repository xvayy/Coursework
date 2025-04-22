#ifndef PACKAGINGWORKSHOP_H
#define PACKAGINGWORKSHOP_H

#include "DigitalScale.h"

// Клас-ітератор для обходу масиву DigitalScale
class ScaleIterator {
private:
    DigitalScale* ptr; // Вказівник на поточний елемент
    int size;          // Розмір масиву
    int index;         // Поточний індекс

public:
    ScaleIterator(DigitalScale* start, int size, int index = 0);

    DigitalScale& operator*();
    ScaleIterator& operator++();
    bool operator!=(const ScaleIterator& other) const;
};

// Клас Фасувальний Цех
class PackagingWorkshop {
private:
    DigitalScale* scales; // Динамічний масив ваг
    int capacity;         // Максимальна місткість масиву
    int count;            // Поточна кількість елементів
    double targetWeight;  // Загальна вага для фасування

public:
    PackagingWorkshop(double target = 0.0, int initialCapacity = 10);
    ~PackagingWorkshop();

    void addScale(const DigitalScale& scale);
    void packageProduct();
    double calculateTotalError() const;
    double calculateTotalPrice() const;

    // Методи для ітератора
    ScaleIterator begin();
    ScaleIterator end();
};

#endif // PACKAGINGWORKSHOP_H