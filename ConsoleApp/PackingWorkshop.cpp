#include "PackingWorkshop.h"
#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

PackingWorkshop::PackingWorkshop(string spec,
	Product prod) {
    specialization = spec;
    product = prod;
    currentScale = nullptr;
}

void PackingWorkshop::displayInfo() {
	product.displayProductInfo();
    cout << "Packed packages: " << packageCount << endl;
    cout << "============================\n";
}

bool PackingWorkshop::startWeighing(double amount) {
    DigitalScale* scale = currentScale;
    if (!scale) {
        cout << "No scale selected.\n";
        return false;
    }
    if (amount > product.getQuantity()) {
        cout << "Not enough product.\n";
        return false;
    }
    if (amount < scale->getMinWeight() || amount > scale->getMaxWeight()) {
        cout << "Amount out of scale range.\n";
        return false;
    }
    if (amount <= 0) {
        cout << "Amount must be positive number.\n";
        return false;
    }

    scale->addWeight(amount);
    product.setQuantity(product.getQuantity() - amount);
    return true;
}

void PackingWorkshop::startPacking() {
    DigitalScale* scale = currentScale;
    if (!scale) {
        cout << "No scale selected.\n";
        return;
    }
    scale->setUnitPrice(product.getUnitPrice());
    double weightOnScale = scale->getMeasuredWeight();
    if (weightOnScale < product.getPackageWeight()) {
        product.setQuantity(product.getQuantity() + weightOnScale);
        scale->resetWeight();
        cout << "Not enough weight for a package.\n";
        return;
    }
    int newPackages = (weightOnScale / product.getPackageWeight());
    double usedWeight = newPackages * product.getPackageWeight();
    double leftover = weightOnScale - usedWeight;

    packageCount += newPackages;
    product.setQuantity(product.getQuantity() + leftover);
    totalPrice += newPackages * scale->getUnitPrice();
    scale->resetWeight();

    cout << "Packed " << newPackages << " packages. Returned " << leftover << " kg to stock.\n";
}

const DigitalScale* PackingWorkshop::getSelectedScale() const {
    return currentScale;
}

DigitalScale* PackingWorkshop::getSelectedScale() {
    return currentScale;
}


int PackingWorkshop::getPackageCount() const { return packageCount; }
double PackingWorkshop::getTotalPrice() const { return totalPrice; }

void PackingWorkshop::setPackageCount(int count) {
    if (count < 0) {
        throw invalid_argument("Package count must be non-negative.");
    }
    packageCount = count;
}

void PackingWorkshop::setCurrentScale(DigitalScale* scale)
{
    currentScale = scale;
}

// Делегати Product
double PackingWorkshop::getProductQuantity() const {
    return product.getQuantity();
}
double PackingWorkshop::getUnitPrice() const {
    return product.getUnitPrice();
}
double PackingWorkshop::getPackageWeight() const {
    return product.getPackageWeight();
}
string PackingWorkshop::getProductName() const {
    return product.getName();
}
void PackingWorkshop::setUnitPrice(double price) {
	product.setUnitPrice(price);
}
void PackingWorkshop::setPackageWeight(double weight) {
	product.setPackageWeight(weight);
}
void PackingWorkshop::setProductName(const string& name) {
    product.setProductName(name);
}
void PackingWorkshop::setProductQuantity(double quantity) {
    if (quantity < 0) {
        throw invalid_argument("Quantity must be non-negative.");
    }
    product.setQuantity(quantity);
    //productQuantity = quantity;
}