#ifndef REALNUMBER_H
#define REALNUMBER_H

#include "Number.h"
#include <iostream>
using namespace std;

class RealNumber : public Number {
private:
    double minRange;
    double maxRange;
    
public:
    // Конструктори
    RealNumber();
    RealNumber(double val, double min, double max);
    RealNumber(const RealNumber& other); 
    RealNumber(RealNumber&& other) noexcept; 
	~RealNumber();

    // Перевірка діапазону
    bool isInRange(double val) const; 

    void print() const override;

	// Геттери і сеттери
    double getValue() const override;
    void setValue(double val) override;

    double getMaxRange() const;
    double getMinRange() const;
    void setMaxRange(double max);
    void setMinRange(double min);



    // Перевантаження операторів
    RealNumber operator+(const RealNumber& other) const;
    RealNumber operator-(const RealNumber& other) const;
    RealNumber operator*(const RealNumber& other) const;
    RealNumber operator/(const RealNumber& other) const;
    double operator()() const; // Дробова частина
    int operator[](int index) const; // Ціла частина
    RealNumber& operator=(const RealNumber& other); // Присвоєння
    RealNumber& operator=(RealNumber&& other) noexcept; // Переміщення

    // Потокові оператори
    friend ostream& operator<<(ostream& os, const RealNumber& rn);
    friend istream& operator>>(istream& is, RealNumber& rn);
};

#endif 