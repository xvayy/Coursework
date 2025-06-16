#include "DigitalScale.h"
#include <stdexcept>
#include <sstream>
#include <random>

DigitalScale::DigitalScale()
    : id(0), weight(0.0, 0.0, 100.0),
    weighingError(0.01), unitPrice(1.0) {
    //cout << "\nDefault DigitalScale was created\n";
}

DigitalScale::DigitalScale(int id, double weight, double min, double max, double error, double price)
    : id(id), weight(weight, min, max), weighingError(error), unitPrice(price) {
    if (error < 0) {
        throw invalid_argument("Error margin cannot be negative");
    }
    if (price < 0) {
        throw invalid_argument("Unit price cannot be negative");
    }
}

DigitalScale::~DigitalScale()
{
    //cout << "\nDigitalScale was destroyed (" << weight << ", " << weighingError << ", " << unitPrice << ")";
}

double DigitalScale::getWeight() const {
    return weight.getValue();
}

double DigitalScale::getWeighingError() const {
    return weighingError;
}

double DigitalScale::getUnitPrice() const {
    return unitPrice;
}

int DigitalScale::getId() const {
	return id;
}

double DigitalScale::getMaxWeight() const {
    return weight.getMaxRange();
}

double DigitalScale::getMinWeight() const {
    return weight.getMinRange();
}

void DigitalScale::setId(int newId)
{
	if (newId < 0) {
		throw invalid_argument("ID cannot be negative");
	}
    id = newId;
}

void DigitalScale::setWeight(double weight) {
    this->weight.setValue(weight);
}

void DigitalScale::setMinWeight(double weight) {
    this->weight.setMinRange(weight);
}

void DigitalScale::setMaxWeight(double weight) {
    this->weight.setMaxRange(weight);
}

void DigitalScale::setWeighingError(double error) {
    if (error < 0) {
        throw invalid_argument("Error margin cannot be negative");
    }
    weighingError = error;
}

double DigitalScale::getMeasuredWeight() const {
	return weight.getValue() + this->generateWeighingError();
}

void DigitalScale::resetWeight()
{
    setWeight(0);
}

void DigitalScale::setUnitPrice(double price) {
    if (price < 0) {
        throw invalid_argument("Unit price cannot be negative");
    }
    unitPrice = price;
}

double DigitalScale::calculateTotalPrice() const {
    return weight.getValue() * unitPrice;
}

void DigitalScale::addWeight(double delta) {
    double err = generateWeighingError();
    setWeight(getWeight() + delta);
    logWeighing(delta, err);
}

void DigitalScale::subtractWeight(double delta) {
    double err = generateWeighingError();
    setWeight(getWeight() - delta);
    logWeighing(-delta, err);
}

double DigitalScale::generateWeighingError() const {
    static random_device rd;
    static mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-weighingError, weighingError);
    return dis(gen);

}

void DigitalScale::info() {
    cout << "  Current Weight: " << getWeight() << " kg\n";
    cout << "  Weighing Error: ±" << weighingError << " kg\n";
    cout << "  Unit Price: " << unitPrice << " UAH/kg\n";
    cout << "  Total Price: " << calculateTotalPrice() << " UAH\n";
    cout << "  Min Weight: " << getMinWeight() << " kg\n";
    cout << "  Max Weight: " << getMaxWeight() << " kg\n\n";
}


void DigitalScale::logWeighing(double mass, double error) {
    weighingLog.push_back({ mass, error });
}

const vector<WeighingEntry>& DigitalScale::getWeighingLog() const {
    return weighingLog;
}

string DigitalScale::toCSVRow() const {
    ostringstream oss;
    oss << id << "," << weight.getValue() << "," << weight.getMinRange() << "," << weight.getMaxRange()
        << "," << weighingError << "," << unitPrice << "\n";
    return oss.str();
}

void DigitalScale::fromCSVRow(const string& row) {
    istringstream iss(row);
    string token;
    getline(iss, token, ','); id = stoi(token);
    getline(iss, token, ','); double w = stod(token);
    getline(iss, token, ','); double min = stod(token);
    getline(iss, token, ','); double max = stod(token);
    getline(iss, token, ','); weighingError = stod(token);
    getline(iss, token, ','); unitPrice = stod(token);
    weight = RealNumber(w, min, max);
}

bool DigitalScale::editField(const string& fieldName) {
    if (fieldName == "min") {
        double newMin;
        std::cout << "Enter new MIN weight: ";
        std::cin >> newMin;
        setMinWeight(newMin);
    }
    else if (fieldName == "max") {
        double newMax;
        std::cout << "Enter new MAX weight: ";
        std::cin >> newMax;
        setMaxWeight(newMax);
    }
    else if (fieldName == "error") {
        double newError;
        std::cout << "Enter new WEIGHING ERROR: ";
        std::cin >> newError;
        setWeighingError(newError);
    }
    else if (fieldName == "price") {
        double newPrice;
        std::cout << "Enter new UNIT PRICE: ";
        std::cin >> newPrice;
        setUnitPrice(newPrice);
    }
    else {
        std::cout << "Unknown field: " << fieldName << std::endl;
        return false;
    }
    return true;
}



ostream& operator<<(ostream& os, const DigitalScale& ds) {
    os << "\nCurrent Weight: " << ds.weight << " kg\n"
     << "  Weighing Error: ±" << ds.weighingError << " kg\n"
     << "  Unit Price: " << ds.unitPrice << " UAH/kg\n"
     << "  Total Price: " << ds.calculateTotalPrice() << " UAH\n"
     << "  Min Weight: " << ds.getMinWeight() << " kg\n"
     << "  Max Weight: " << ds.getMaxWeight() << " kg\n\n";
	return os;
}

istream& operator>>(istream& is, DigitalScale& ds) {
	cout << "Enter weight: ";
	is >> ds.weight;
	if (!ds.weight.isInRange(ds.weight.getValue())) {
		throw out_of_range("Weight is out of range");
	}
    cout << "Enter error: ";
	is >> ds.weighingError;
	if (ds.weighingError < 0) {
		throw invalid_argument("Weighing error cannot be negative");
	}
    cout << "Enter unit price: ";
	is >> ds.unitPrice;
	if (ds.unitPrice < 0) {
		throw invalid_argument("Unit price cannot be negative");
	}
	return is;
}

ofstream& operator<<(ofstream& ofs, const DigitalScale& ds) {
    ofs << ds.toCSVRow();
    return ofs;
}

ifstream& operator>>(ifstream& ifs, DigitalScale& ds) {
    string line;
    if (!getline(ifs, line)) return ifs;
    ds.fromCSVRow(line);
    return ifs;
}

