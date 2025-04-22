#ifndef DIGITALSCALE_H
#define DIGITALSCALE_H

#include "RealNumber.h"

class DigitalScale : public RealNumber {
private:
    double errorMargin;
    double unitPrice;
    double totalPrice;

public:
    DigitalScale(double weight = 0.0, double error = 0.01, double price = 1.0, double min = 0.0, double max = 1000.0);
    DigitalScale(const DigitalScale& other);
    DigitalScale(DigitalScale&& other) noexcept;
    ~DigitalScale() override;

    double getWeight() const;
    double getErrorMargin() const;
    double calculateTotalPrice() const;

    DigitalScale& operator=(const DigitalScale& other); // Додаємо оператор присвоєння
    DigitalScale& operator=(DigitalScale&& other) noexcept; // Додаємо оператор присвоєння переміщення

    void display() const override;
};

#endif // DIGITALSCALE_H