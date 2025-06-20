﻿#pragma once
#include "DigitalScale.h"
#include "Product.h"
#include "ScaleManager.h"
#include <string>
#include <fstream>

class PackingWorkshop {
private:
    string specialization;
    double totalPrice = 0;
    double totalPackedprice = 0;
    int packageCount = 0;
	Product product;
    double markupPercentage = 50;

    DigitalScale* currentScale = nullptr;
public:
    PackingWorkshop(string spec, Product prod);

    void displayInfo();
    bool startWeighing(double amount);
    void startPacking();
	void updateTotals(int newPackages);

    double getTotalPackagePrice() const;

    // Гетери
    DigitalScale* getCurrentScale();
    int getPackageCount() const;
    double getTotalPrice() const;

    // Сетери
    void setPackageCount(int count);
    void setCurrentScale(DigitalScale* scale);

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
