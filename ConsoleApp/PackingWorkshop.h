#pragma once
#include "DigitalScale.h"
#include "AbstractScaleManager.h"
#include <string>
#include <fstream>

class PackingWorkshop {
private:
    string specialization;
    string productName = "No name";
    double productQuantity = 0;
    double unitPrice = 0;
    double packageWeight = 0;
    double totalPrice = 0;
    int packageCount = 0;

    AbstractScaleManager* scaleManager = nullptr;

public:
    PackingWorkshop(AbstractScaleManager* manager, const string& spec,
        const string& product, double quantity,
        double price, double pkgWeight, int pkgCount);

    void displayProductInfo() const;
    bool weighProduct(double amount);
    void packProduct();
    void generateReport(const string& filename) const;

    // Гетери
    DigitalScale* getSelectedScale();
    const DigitalScale* getSelectedScale() const;
    string getProductName() const;
    double getProductQuantity() const;
    double getUnitPrice() const;
    double getPackageWeight() const;
    int getPackageCount() const;
    double getTotalPrice() const;

	// Сетери
    void setProductQuantity(double quantity);
    void setPackageCount(int count);
};
