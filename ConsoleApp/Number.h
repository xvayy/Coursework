#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>

class Number {
protected:
    double value;

public:
	Number() = default;
    Number(double val);
    virtual ~Number();
    virtual void print() const; 
    virtual double getValue() const;
    virtual void setValue(double val);
};

#endif