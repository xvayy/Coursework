#ifndef REALNUMBER_H
#define REALNUMBER_H

#include <iostream>

class RealNumber {
protected:
    double value;
    const double minRange;
    const double maxRange;

public:
    RealNumber(double val = 0.0, double min = -1000.0, double max = 1000.0);
    RealNumber(const RealNumber& other);
    RealNumber(RealNumber&& other) noexcept;
    virtual ~RealNumber();

    bool isInRange(double val) const;
    void setValue(double val);
    double getValue() const;

    RealNumber operator+(const RealNumber& other) const;
    RealNumber operator-(const RealNumber& other) const;
    RealNumber operator*(const RealNumber& other) const;
    RealNumber operator/(const RealNumber& other) const;
    double operator()() const;
    double operator[](int) const;
    RealNumber& operator=(const RealNumber& other);
    RealNumber& operator=(RealNumber&& other) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const RealNumber& num);
    friend std::istream& operator>>(std::istream& is, RealNumber& num);

    virtual void display() const;
};

#endif // REALNUMBER_H