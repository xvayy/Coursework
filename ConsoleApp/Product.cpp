#include "Product.h"


Product::Product() = default;

Product::Product(const string name, double quantity, double unitPrice, double packageWeight) {
    if (name.empty()) throw std::invalid_argument("Product name cannot be empty.");
    if (quantity < 0) throw std::invalid_argument("Quantity must be non-negative.");
    if (unitPrice < 0) throw std::invalid_argument("Unit price must be non-negative.");
    if (packageWeight <= 0) throw std::invalid_argument("Package weight must be positive.");
	this->name = name;
	this->quantity = quantity;
	this->unitPrice = unitPrice;
	this->packageWeight = packageWeight;
}

void Product::displayProductInfo() {
    cout << "\n=== Product Information ===\n";
    cout << "Product name: " << name << endl;
    cout << "Available amount: " << quantity << " kg" << endl;
    cout << "Unit price: " << unitPrice << " UAH/kg" << endl;
    cout << "Package weight: " << packageWeight << " kg" << endl;
}

const string Product::getName() const {
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
    if (q < 0) throw invalid_argument("Quantity must be non-negative.");
    quantity = q;
}

void Product::setUnitPrice(double p) {
    if (p < 0) throw invalid_argument("Unit price must be non-negative.");
    unitPrice = p;
}

void Product::setPackageWeight(double w) {
    if (w <= 0) throw invalid_argument("Package weight must be positive.");
    packageWeight = w;
}

void Product::setProductName(const string name) {
    if (name.empty()) throw invalid_argument("Product name cannot be empty.");
    this->name = name;
}