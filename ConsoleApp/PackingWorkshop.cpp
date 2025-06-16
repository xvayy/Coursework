#include "PackingWorkshop.h"
#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

PackingWorkshop::PackingWorkshop(ScaleManager* manager, const string& spec,
	Product prod) {
	scaleManager = manager;
	specialization = spec;
	product = prod;
}

void PackingWorkshop::displayProductInfo() const {
	cout << "\n=== Product Information ===\n";
    cout << "Product name: " << product.getName() << endl;
    cout << "Available amount: " << product.getQuantity() << " kg" << endl;
    cout << "Unit price: " << product.getUnitPrice() << " UAH/kg" << endl;
    cout << "Package weight: " << product.getPackageWeight() << " kg" << endl;
    cout << "Packed packages: " << packageCount << endl;
    cout << "============================\n";
}

bool PackingWorkshop::startWeighing(double amount) {
    DigitalScale* scale = scaleManager->getSelectedScale();
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
    double prodQuant = product.getQuantity();
    prodQuant -= amount;
    product.setQuantity(prodQuant);

    return true;
}

void PackingWorkshop::startPacking() {
    DigitalScale* scale = scaleManager->getSelectedScale();
    if (!scale) {
        cout << "No scale selected.\n";
        return;
    }
    double weightOnScale = scale->getMeasuredWeight();
    if (weightOnScale < product.getPackageWeight()) {
		double prodQuant = product.getQuantity();
		prodQuant += weightOnScale;
        product.setQuantity(prodQuant);
        scale->resetWeight();
        cout << "Not enough weight for a package.\n";
        return;
    }
    int newPackages = static_cast<int>(weightOnScale / product.getPackageWeight());
    double usedWeight = newPackages * product.getPackageWeight();
    double leftover = weightOnScale - usedWeight;

    packageCount += newPackages;
    //productQuantity += leftover;
    product.setQuantity(product.getQuantity() + leftover);
    totalPrice += newPackages * product.getUnitPrice();
    scale->resetWeight();

    cout << "Packed " << newPackages << " packages. Returned " << leftover << " kg to stock.\n";
}

const DigitalScale* PackingWorkshop::getSelectedScale() const {
    return scaleManager->getSelectedScale();
}

DigitalScale* PackingWorkshop::getSelectedScale() {
    return scaleManager->getSelectedScale();
}

int PackingWorkshop::getPackageCount() const { return packageCount; }
double PackingWorkshop::getTotalPrice() const { return totalPrice; }

void PackingWorkshop::setPackageCount(int count) {
    if (count < 0) {
        throw invalid_argument("Package count must be non-negative.");
    }
    packageCount = count;
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
std::string PackingWorkshop::getProductName() const {
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