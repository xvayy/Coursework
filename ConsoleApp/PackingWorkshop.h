#ifndef PACKING_SHOP_H
#define PACKING_SHOP_H

#include "DigitalScale.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class PackingWorkshop {
private:
    DigitalScale* scales;
    int size;
    int capacity;
    string specialization;
    void resize();

    int nextScaleId = 1;
    DigitalScale* selectedScale = nullptr;

    string productName = "No name";
	double productQuantity = 0;
    double unitPrice = 0;
    double packageWeight = 0;
    int packageCount = 0;

    double totalPrice = 0;

public:
    PackingWorkshop();
    PackingWorkshop(const string spec, string product, double productQuantity,
        double unitPrice, double packageWeight, int packageCount);
    PackingWorkshop(const PackingWorkshop& other);
    PackingWorkshop(PackingWorkshop&& other) noexcept;
    ~PackingWorkshop();

    PackingWorkshop& operator=(const PackingWorkshop& other);
    PackingWorkshop& operator=(PackingWorkshop&& other) noexcept;

    // Гетери
    DigitalScale* getSelectedScale() const;
    string getProductName() const;
    double getProductQuantity() const;
    double getUnitPrice() const;
    double getPackageWeight() const;
    int getPackageCount() const;

    // Сетери
    void setProductName(const string& name);
    void setProductQuantity(double quantity);
    void setUnitPrice(double price);
    void setPackageWeight(double weight);
    void setPackageCount(int count);

    // Методи для роботи з вагами
    void displayScales() const; 
    void addScale(const DigitalScale& scale); 
    void removeScale(size_t index);
    void displayScaleInfo(size_t index) const;
    void selectScale(int scaleId);
    void saveScalesToCSV(const string& filename) const;
    void loadScalesFromCSV(const std::string& filename);
    bool loadScaleByIdFromCSV(const string& filename, int id, DigitalScale& scale) const;

	double getTotalPrice() const;
    double calculateTotalWeighingError() const;
    int findScaleIndexById(int id) const;
    void editScaleById(int id, const vector<string>& fieldsToEdit);

    void displayProductInfo() const;


    bool weighProduct(double amount);
    void packProduct();
    void generateReport(const string& filename) const;

    // 💀💀💀💀💀💀
    friend ostream& operator<<(ostream& os, const PackingWorkshop& pw);
    friend istream& operator>>(istream& is, PackingWorkshop& pw);







    // --------------------------------------------------------------------------------------------
    class Iterator {
    private:
        DigitalScale* current;
    public:
        Iterator(DigitalScale* ptr);
        DigitalScale& operator*();
        DigitalScale* operator->();
        Iterator& operator++();
        Iterator& operator=(const Iterator& other);
        bool operator!=(const Iterator& other);
        bool operator==(const Iterator& other);
    };

    Iterator begin() const;

    Iterator end() const;

};


#endif 
