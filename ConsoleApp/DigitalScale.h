#ifndef DIGITAL_SCALE_H
#define DIGITAL_SCALE_H

#include "RealNumber.h"
#include <string>
using namespace std;

class DigitalScale {
private:
    RealNumber weight;
    double weighingError;
    double unitPrice;
    int id;

public:
    DigitalScale();
    DigitalScale(int id, double weight, double min, double max, double error, double price);
    ~DigitalScale();

    // Геттери і сеттери
    double getWeight() const;
    double getMaxWeight() const;
    double getMinWeight() const;
    double getWeighingError() const;
    double getUnitPrice() const;
    int getId() const;


    void setWeight(double weight);
    void setMinWeight(double weight);
    void setMaxWeight(double weight);
    void setWeighingError(double error);
    void setUnitPrice(double price);
	void setId(int newId);


    double calculateTotalPrice() const;
    double generateWeighingError() const;
    void addWeight(double delta);
    void subtractWeight(double delta);

    void info();




    // сsv☠️☠️☠️☠️☠️☠️☠️☠️☠️
    string toCSVRow() const;
    void fromCSVRow(const string& row);
    bool editField(const string& fieldName);

    friend ostream& operator<<(ostream& os, const DigitalScale& ds);
    friend istream& operator>>(istream& is, DigitalScale& ds);

};

#endif 