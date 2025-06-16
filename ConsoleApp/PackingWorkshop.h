#pragma once
#include "DigitalScale.h"
#include "Product.h"
#include "ScaleManager.h"
#include <string>
#include <fstream>

class PackingWorkshop {
private:
    string specialization;
    double totalPrice = 0;
    int packageCount = 0;

	Product product;
    ScaleManager* scaleManager = nullptr;

public:
    PackingWorkshop(ScaleManager* manager, const string& spec, Product prod);

    void displayProductInfo() const;
    bool startWeighing(double amount);
    void startPacking();

    // Гетери
    DigitalScale* getSelectedScale();
    const DigitalScale* getSelectedScale() const;
    int getPackageCount() const;
    double getTotalPrice() const;

	// Сетери
    void setPackageCount(int count);

    // Делегати Product
    double getProductQuantity() const;
    double getUnitPrice() const;
    double getPackageWeight() const;
    string getProductName() const;

    void setProductQuantity(double quantity);
    void setUnitPrice(double price);
    void setPackageWeight(double weight);
    void setProductName(const string& name);
};
