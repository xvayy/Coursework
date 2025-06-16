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
    // ������������
    RealNumber();
    RealNumber(double val, double min, double max);
    RealNumber(const RealNumber& other); 
    RealNumber(RealNumber&& other) noexcept; 
	~RealNumber();

    // �������� ��������
    bool isInRange(double val) const; 

    void print() const override;

	// ������� � �������
    double getValue() const override;
    void setValue(double val) override;

    double getMaxRange() const;
    double getMinRange() const;
    void setMaxRange(double max);
    void setMinRange(double min);



    // �������������� ���������
    RealNumber operator+(const RealNumber& other) const;
    RealNumber operator-(const RealNumber& other) const;
    RealNumber operator*(const RealNumber& other) const;
    RealNumber operator/(const RealNumber& other) const;
    double operator()() const; // ������� �������
    int operator[](int index) const; // ֳ�� �������
    RealNumber& operator=(const RealNumber& other); // ���������
    RealNumber& operator=(RealNumber&& other) noexcept; // ����������

    // ������� ���������
    friend ostream& operator<<(ostream& os, const RealNumber& rn);
    friend istream& operator>>(istream& is, RealNumber& rn);
};

#endif 