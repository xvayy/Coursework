#include "PackingWorkshop.h"

#include <sstream>
#include <iostream>
#include <stdexcept>


PackingWorkshop::PackingWorkshop() {
	size = 0;
	capacity = 1;
	scales = new DigitalScale[capacity];
}

PackingWorkshop::PackingWorkshop(const string spec, string product, double productQuantity,
    double unitPrice, double packageWeight, int packageCount) : specialization(spec), productName(product), productQuantity(productQuantity),
	unitPrice(unitPrice), packageWeight(packageWeight), packageCount(packageCount)
{
    size = 0;
    capacity = 1;
	scales = new DigitalScale[capacity];
}

// Конструктор копіювання
PackingWorkshop::PackingWorkshop(const PackingWorkshop& other)
    : size(other.size), capacity(other.capacity)
{
    scales = new DigitalScale[capacity];
    for (int i = 0; i < size; ++i) {
        scales[i] = other.scales[i];
    }
}

// Конструктор переміщення
PackingWorkshop::PackingWorkshop(PackingWorkshop&& other) noexcept
    : size(other.size), capacity(other.capacity), scales(other.scales)
{
    other.scales = nullptr;
    other.size = 0;
    other.capacity = 0;
}

PackingWorkshop::~PackingWorkshop() {
    delete[] scales;
}

// копіювання
PackingWorkshop& PackingWorkshop::operator=(const PackingWorkshop& other)
{
    if (this != &other) {
        delete[] scales;
        size = other.size;
        capacity = other.capacity;
        /*products = other.products;
        csvFile = other.csvFile*/;
        scales = new DigitalScale[capacity];
        for (int i = 0; i < size; ++i) {
            scales[i] = other.scales[i];
        }
    }
    return *this;
}

// переміщення
PackingWorkshop& PackingWorkshop::operator=(PackingWorkshop&& other) noexcept
{
    if (this != &other) {
        delete[] scales;
        size = other.size;
        capacity = other.capacity;
        // products = std::move(other.products);
        // csvFile = std::move(other.csvFile);
        scales = other.scales;
        other.scales = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
}

DigitalScale* PackingWorkshop::getSelectedScale() const {
    return selectedScale;
}
string PackingWorkshop::getProductName() const {
    return productName;
}
double PackingWorkshop::getProductQuantity() const {
    return productQuantity;
}
double PackingWorkshop::getUnitPrice() const {
    return unitPrice;
}
double PackingWorkshop::getPackageWeight() const {
    return packageWeight;
}
int PackingWorkshop::getPackageCount() const {
    return packageCount;
}


void PackingWorkshop::setProductName(const string& name) {
    if (name.empty()) {
        throw invalid_argument("Product name cannot be empty.");
    }
    productName = name;
}
void PackingWorkshop::setProductQuantity(double quantity) {
    if (quantity < 0) {
        throw invalid_argument("Product quantity cannot be negative.");
    }
    productQuantity = quantity;
}
void PackingWorkshop::setUnitPrice(double price) {
    if (price < 0) {
        throw invalid_argument("Unit price cannot be negative.");
    }
    unitPrice = price;
}
void PackingWorkshop::setPackageWeight(double weight) {
    if (weight <= 0) {
        throw invalid_argument("Package weight must be positive.");
    }
    packageWeight = weight;
}
void PackingWorkshop::setPackageCount(int count) {
    if (count < 0) {
        throw invalid_argument("Package count cannot be negative.");
    }
    packageCount = count;
}

double PackingWorkshop::getTotalPrice() const { return totalPrice; }


void PackingWorkshop::resize() {
	if (size >= capacity) {
		capacity *= 2;
		DigitalScale* newScales = new DigitalScale[capacity];
		for (int i = 0; i < size; ++i) {
			newScales[i] = scales[i];
		}
		delete[] scales;
		scales = newScales;
	}
}

void PackingWorkshop::displayScales() const {
	if (size == 0) {
		cout << "No scales available.\n";
		return;
	}
	cout << "Available scales:\n";
    cout << "----------------------------------------------\n";

	for (int i = 0; i < size; ++i) {
		cout << "Scale ID: " << scales[i].getId() << ":\n";
		scales[i].info();
		cout << "----------------------------------------------\n";
	}
	return; 
}

void PackingWorkshop::addScale(const DigitalScale& scale) {
    resize();
    DigitalScale newScale = scale;
    newScale.setId(nextScaleId++);
    scales[size++] = newScale;
}

void PackingWorkshop::removeScale(size_t index) {
    if (index >= size) {
        throw out_of_range("Invalid scale index.");
    }
	if (size == 0) {
		throw runtime_error("No scales to remove.");
	}
    for (size_t i = index; i < size - 1; ++i) {
        scales[i] = scales[i + 1];
    }
    size--;
}

void PackingWorkshop::displayScaleInfo(size_t index) const {
    if (index >= size) {
        throw out_of_range("Invalid scale index.");
    }
    cout << "Scale #" << index + 1 << " info:\n";
    scales[index].info();
}

// Загална похибка зважування
double PackingWorkshop::calculateTotalWeighingError() const {
    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        double mass = scales[i].getWeight();       
        double error = scales[i].getWeighingError();
    	sum += pow(mass * error, 2);                 
    }
    return sqrt(sum);
}


int PackingWorkshop::findScaleIndexById(int id) const {
    for (int i = 0; i < size; ++i) {
        if (scales[i].getId() == id) return i;
    }
    return -1;
}

void PackingWorkshop::saveScalesToCSV(const string& filename) const {
    ofstream file(filename);
    file << "id,weight,min,max,error,unitPrice\n";
    for (int i = 0; i < size; ++i) {
        file << scales[i].toCSVRow() << "\n";
    }
    file.close();
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ахтунг
bool PackingWorkshop::loadScaleByIdFromCSV(const string& filename, int id, DigitalScale& scale) const {
    ifstream file(filename);
    string line;
    getline(file, line); // скіпнути заголовок
    //size = 0;
    while (getline(file, line)) {
        istringstream iss(line);
        string token;
        getline(iss, token, ',');
        int curId = std::stoi(token);
        if (curId == id) {
            scale.fromCSVRow(line);
            return true;
        }
    }
    return false;
}

void PackingWorkshop::loadScalesFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        DigitalScale scale;
        scale.fromCSVRow(line);
        addScale(scale);
    }

    file.close();
}


void PackingWorkshop::editScaleById(int id, const std::vector<std::string>& fieldsToEdit) {
    int idx = findScaleIndexById(id);
    if (idx == -1) {
        std::cout << "Scale with id=" << id << " not found.\n";
        return;
    }

    for (const std::string& field : fieldsToEdit) {
        if (!scales[idx].editField(field)) {
            std::cout << "Skipping unknown field: " << field << std::endl;
        }
    }

    std::cout << "Editing completed.\n";
}

void PackingWorkshop::displayProductInfo() const {
    cout << "Product name: " << productName << endl;
    cout << "Available quantity: " << productQuantity << " kg" << endl;
    cout << "Unit price: " << unitPrice << " UAH/kg" << endl;
    cout << "Package weight: " << packageWeight << " kg" << endl;
    cout << "Packed packages: " << packageCount << endl;
}


void PackingWorkshop::selectScale(int scaleId) {
    int idx = findScaleIndexById(scaleId);
    if (idx == -1) {
        cout << "Scale not found.\n";
        selectedScale = nullptr;
    }
    else {
        selectedScale = &scales[idx];
        cout << "Scale with ID " << scaleId << " selected.\n";
    }
}

bool PackingWorkshop::weighProduct(double amount) {
    if (!selectedScale) {
        cout << "No scale selected.\n";
        return false;
    }
    if (amount > productQuantity) {
        cout << "Not enough product.\n";
        return false;
    }
    if (amount < selectedScale->getMinWeight() || amount > selectedScale->getMaxWeight()) {
        cout << "Amount out of scale range.\n";
        return false;
    }
    selectedScale->addWeight(amount);
    productQuantity -= amount;
    return true;
}

void PackingWorkshop::packProduct() {
    if (!selectedScale) {
        cout << "No scale selected.\n";
        return;
    }
    double weightOnScale = selectedScale->getWeight();
    if (weightOnScale < packageWeight) {
        productQuantity += weightOnScale;
        selectedScale->setWeight(0);
        cout << "Not enough weight for a package.\n";
        return;
    }
    int newPackages = weightOnScale / packageWeight;
    double usedWeight = newPackages * packageWeight;
    double leftover = weightOnScale - usedWeight;

    packageCount += newPackages;
    productQuantity += leftover;
    selectedScale->setWeight(0);

    totalPrice += newPackages * packageWeight * unitPrice;

    cout << "Packed " << newPackages << " packages. Returned " << leftover << " kg to stock.\n";
}

void PackingWorkshop::generateReport(const string& filename) const {
    ofstream file(filename);
    file << "Product: " << productName << "\n";
    file << "Total packed: " << packageCount << " packages\n";
    file << "Remaining product: " << productQuantity << " kg\n";
    file << "Unit price: " << unitPrice << " UAH/kg\n";
    file << "Total value packed: " << packageCount * packageWeight * unitPrice << " UAH\n";
    file << "Total weighing error: " << calculateTotalWeighingError() << " kg\n";
    file.close();
    cout << "Report saved to " << filename << endl;
}



/*
void PackingWorkshop::loadProductsFromCSV() {
    string fileName = specialization + ".csv";
    ifstream file(fileName);
    if (!file.is_open()) {
        throw runtime_error("Unable to open product file.");
    }

    string line;
    getline(file, line);

    cout << "\nProduct List:\n";

    while (getline(file, line)) {
        stringstream ss(line);
        string name, quantityStr, priceStr, weightStr, countStr;

        getline(ss, name, ',');
        getline(ss, quantityStr, ',');
        getline(ss, priceStr, ',');
        getline(ss, weightStr, ',');
        getline(ss, countStr, ',');

        cout << "Product name: " << name << "\n"
            << "Quantity: " << quantityStr << " kg\n"
            << "Price per kg: " << priceStr << " UAN/kg\n"
            << "Package weight: " << weightStr << " kg\n"
            << "Amount of packed packages: " << countStr << "\n"
            << "-----------------------------\n";
    }

    file.close();
}

void PackingWorkshop::saveProductsToCSV() {
    string fileName = specialization + ".csv";

    // Якщо файл не існує або порожній — записати заголовок
    bool writeHeader = !fileExists(fileName) || ifstream(fileName).peek() == ifstream::traits_type::eof();

    ofstream file(fileName, ios::app);
    if (!file.is_open()) {
        throw runtime_error("Cannot write to CSV file: " + fileName);
    }

    if (writeHeader) {
        file << "productName,quantity,unitPrice,packageWeight,packageCount\n";
    }

    string name;
    double quantity;
    double unitPrice;
    double packageWeight;

    cout << "Enter product name: ";
    cin >> name;
    cout << "Enter quantity (kg): ";
    cin >> quantity;
    cout << "Enter unit price (UAH/kg): ";
    cin >> unitPrice;
    cout << "Enter package weight (kg): ";
    cin >> packageWeight;

    int packageCount = 0;

    file << name << "," << quantity << "," << unitPrice << "," << packageWeight << "," << packageCount << "\n";
    file.close();

    cout << "Product saved successfully.\n";
}
*/




















//--------------------------------------------------------------Ітератор ---------------------------------
PackingWorkshop::Iterator::Iterator(DigitalScale* ptr) {
    current = ptr;
}

DigitalScale& PackingWorkshop::Iterator::operator*() {
    return *current;
}
DigitalScale* PackingWorkshop::Iterator::operator->() {
    return current;
}
PackingWorkshop::Iterator& PackingWorkshop::Iterator::operator++() {
    current++;
    return *this;
}
PackingWorkshop::Iterator& PackingWorkshop::Iterator::operator=(const Iterator& other) {
    current = other.current;
    return *this;
}

bool PackingWorkshop::Iterator::operator!=(const Iterator& other) {
    return current != other.current;
}
bool PackingWorkshop::Iterator::operator==(const Iterator& other) {
    return current == other.current;
}

PackingWorkshop::Iterator PackingWorkshop::begin() const {
    return Iterator(scales);
}

PackingWorkshop::Iterator PackingWorkshop::end() const {
    return Iterator(scales + size);
}

// 💀💀💀💀💀💀💀💀💀
ostream& operator<<(ostream& os, const PackingWorkshop& pw) {
    os << pw.specialization << "\n";
    os << pw.size << "\n";

    for (int i = 0; i < pw.size; ++i) {
        os << pw.scales[i].getWeight() << " "
            << pw.scales[i].getMinWeight() << " "
            << pw.scales[i].getMaxWeight() << " "
            << pw.scales[i].getWeighingError() << " "
            << pw.scales[i].getUnitPrice() << "\n";
    }
    return os;
}

istream& operator>>(istream& is, PackingWorkshop& pw) {
    is >> ws; // пропуск пробілів/переносів перед specialization
    getline(is, pw.specialization);

    is >> pw.size;
    pw.capacity = pw.size > 0 ? pw.size : 1;

    delete[] pw.scales;
    pw.scales = new DigitalScale[pw.capacity];

    for (int i = 0; i < pw.size; ++i) {
		int id;
        double w, min, max, error, price;
        is >> id >> w >> min >> max >> error >> price;
        pw.scales[i] = DigitalScale(id,w, min, max, error, price);
    }

    return is;
}
