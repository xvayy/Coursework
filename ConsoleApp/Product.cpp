#include "Product.h"

Product::Product() = default;

Product::Product(const std::string& name, double quantity, double unitPrice, double packageWeight)
    : name(name), quantity(quantity), unitPrice(unitPrice), packageWeight(packageWeight)
{
    if (name.empty()) throw std::invalid_argument("Product name cannot be empty.");
    if (quantity < 0) throw std::invalid_argument("Quantity must be non-negative.");
    if (unitPrice < 0) throw std::invalid_argument("Unit price must be non-negative.");
    if (packageWeight <= 0) throw std::invalid_argument("Package weight must be positive.");
}

const std::string& Product::getName() const {
    return name;
}

double Product::getQuantity() const {
    return quantity;
}

double Product::getUnitPrice() const {
    return unitPrice;
}

double Product::getPackageWeight() const {
    return packageWeight;
}



void Product::setQuantity(double q) {
    if (q < 0) throw std::invalid_argument("Quantity must be non-negative.");
    quantity = q;
}

void Product::setUnitPrice(double p) {
    if (p < 0) throw std::invalid_argument("Unit price must be non-negative.");
    unitPrice = p;
}

void Product::setPackageWeight(double w) {
    if (w <= 0) throw std::invalid_argument("Package weight must be positive.");
    packageWeight = w;
}

void Product::setProductName(const std::string& name) {
    if (name.empty()) throw std::invalid_argument("Product name cannot be empty.");
    this->name = name;
}