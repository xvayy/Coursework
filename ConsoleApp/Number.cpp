#include "Number.h"
#include <iostream>

Number::Number(double val) : value(val) {}

Number::~Number() {}

void Number::print() const
{
	std::cout << "Number value: " << value << std::endl;
}
double Number::getValue() const {
	return value;
}
void Number::setValue(double val) {
	value = val;
}