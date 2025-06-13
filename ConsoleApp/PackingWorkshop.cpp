#include "PackingWorkshop.h"
#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace std;

PackingWorkshop::PackingWorkshop(AbstractScaleManager* manager, const std::string& spec,
    const std::string& product, double quantity,
    double price, double pkgWeight, int pkgCount)
    : scaleManager(manager), specialization(spec), productName(product),
    productQuantity(quantity), unitPrice(price), packageWeight(pkgWeight), packageCount(pkgCount) {
}

void PackingWorkshop::displayProductInfo() const {
	cout << "\n=== Product Information ===\n";
    cout << "Product name: " << productName << endl;
    cout << "Available amount: " << productQuantity << " kg" << endl;
    cout << "Unit price: " << unitPrice << " UAH/kg" << endl;
    cout << "Package weight: " << packageWeight << " kg" << endl;
    cout << "Packed packages: " << packageCount << endl;
    cout << "============================\n";
}

bool PackingWorkshop::weighProduct(double amount) {
    DigitalScale* scale = scaleManager->getSelectedScale();
    if (!scale) {
        cout << "No scale selected.\n";
        return false;
    }
    if (amount > productQuantity) {
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
    productQuantity -= amount;
    return true;
}

void PackingWorkshop::packProduct() {
    DigitalScale* scale = scaleManager->getSelectedScale();
    if (!scale) {
        cout << "No scale selected.\n";
        return;
    }
    double weightOnScale = scale->getMeasuredWeight();
    if (weightOnScale < packageWeight) {
        productQuantity += weightOnScale;
        scale->resetWeight();
        cout << "Not enough weight for a package.\n";
        return;
    }
    int newPackages = static_cast<int>(weightOnScale / packageWeight);
    double usedWeight = newPackages * packageWeight;
    double leftover = weightOnScale - usedWeight;

    packageCount += newPackages;
    productQuantity += leftover;
    totalPrice += usedWeight * unitPrice;
    scale->resetWeight();

    cout << "Packed " << newPackages << " packages. Returned " << leftover << " kg to stock.\n";
}

void PackingWorkshop::generateReport(const std::string& filename) const {
    ofstream file(filename);
    file << "Product: " << productName << "\n";
    file << "Total packed: " << packageCount << " packages\n";
    file << "Remaining product: " << productQuantity << " kg\n";
    file << "Unit price: " << unitPrice << " UAH/kg\n";
    file << "Total value packed: " << totalPrice << " UAH\n";
    file << "---\n";
    cout << "Report saved to " << filename << endl;
}

const DigitalScale* PackingWorkshop::getSelectedScale() const {
    return scaleManager->getSelectedScale();
}

DigitalScale* PackingWorkshop::getSelectedScale() {
    return scaleManager->getSelectedScale();
}

string PackingWorkshop::getProductName() const { return productName; }
double PackingWorkshop::getProductQuantity() const { return productQuantity; }
double PackingWorkshop::getUnitPrice() const { return unitPrice; }
double PackingWorkshop::getPackageWeight() const { return packageWeight; }
int PackingWorkshop::getPackageCount() const { return packageCount; }
double PackingWorkshop::getTotalPrice() const { return totalPrice; }

void PackingWorkshop::setProductQuantity(double quantity) {
    if (quantity < 0) {
        throw invalid_argument("Quantity must be non-negative.");
    }
    productQuantity = quantity;
}

void PackingWorkshop::setPackageCount(int count) {
    if (count < 0) {
        throw invalid_argument("Package count must be non-negative.");
    }
    packageCount = count;
}
