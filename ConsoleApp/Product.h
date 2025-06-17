#pragma once
#include <string>
#include <stdexcept>
#include <iostream>
using namespace std;
class Product {
private:
    std::string name = "No name";
    double quantity = 0.0;
    double unitPrice = 0.0;
    double packageWeight = 0.0;

public:
    Product();

    Product(const string name, double quantity, double unitPrice, double packageWeight);
    void displayProductInfo();

    // Getters
    const string getName() const;
    double getQuantity() const;
    double getUnitPrice() const;
    double getPackageWeight() const;

    // Setters with validation
    void setQuantity(double q);
    void setUnitPrice(double p);
    void setPackageWeight(double w);
    void setProductName(const string name);
};