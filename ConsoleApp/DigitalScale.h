#ifndef DIGITAL_SCALE_H
#define DIGITAL_SCALE_H

#include "RealNumber.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

struct WeighingEntry {
    double mass;
    double error;
};

class DigitalScale {
private:
    RealNumber weight;
    double weighingError;
    double unitPrice;
    int id;


    vector<WeighingEntry> weighingLog;

public:
    DigitalScale();
    DigitalScale(int id, double weight, double min, double max, double error, double price);
    ~DigitalScale();

    // Геттери і сеттери
    double getWeight() const;
    double getMeasuredWeight() const; // вага з похибкою
    void resetWeight();
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

    // Для логування зважування
    void logWeighing(double mass, double error);
    const vector<WeighingEntry>& getWeighingLog() const;


    // сsv☠️☠️☠️☠️☠️☠️☠️☠️☠️
    string toCSVRow() const;
    void fromCSVRow(const string& row);
    bool editField(const string& fieldName);

    friend ostream& operator<<(ostream& os, const DigitalScale& ds);
    friend istream& operator>>(istream& is, DigitalScale& ds);
    friend ofstream& operator<<(ofstream& ofs, const DigitalScale& ds);
    friend ifstream& operator>>(ifstream& ifs, DigitalScale& ds);

};

#endif 