#include "ScaleManager.h"
#include <iostream>
#include <fstream>
#include <cmath>'

using namespace std;

ScaleManager::ScaleManager() {
    size = 0;
    capacity = 1;
    scales = new DigitalScale[capacity];
}

ScaleManager::~ScaleManager() {
    delete[] scales;
}

void ScaleManager::resize() {
    if (size == capacity)
    {
	    capacity *= 2;
	    DigitalScale* newScales = new DigitalScale[capacity];
	    for (int i = 0; i < size; ++i) {
	        newScales[i] = scales[i];
	    }
	    delete[] scales;
        scales = newScales;
    }
}

void ScaleManager::displayScales() const {
    if (size == 0) {
        std::cout << "No scales available.\n";
        return;
    }
    std::cout << "Available scales:\n";
    std::cout << "----------------------------------------------\n";

    ScaleManager::Iterator it = begin();
    ScaleManager::Iterator itEnd = end();

    for (; it != itEnd; ++it) {
        std::cout << "Scale ID: " << (*it).getId() << ":\n";
        (*it).info();
        std::cout << "----------------------------------------------\n";
    }
}

void ScaleManager::addScale(const DigitalScale& scale) {
    resize();
    DigitalScale newScale = scale;
    newScale.setId(nextScaleId++);
    scales[size++] = newScale;
}

void ScaleManager::removeScale(int index) {
    if (index >= size) {
        throw out_of_range("Invalid scale index.");
    }
    for (int i = index; i < size - 1; ++i) {
        scales[i] = scales[i + 1];
    }
    size--;
}

int ScaleManager::findScaleIndexById(int id) const {
    ScaleManager::Iterator it = begin();
    ScaleManager::Iterator itEnd = end();
    int index = 0;

    for (; it != itEnd; ++it, ++index) {
        if ((*it).getId() == id) {
            return index;
        }
    }

    return -1;
}

void ScaleManager::editScaleById(int id, const vector<string>& fieldsToEdit) {
    int idx = findScaleIndexById(id);
    if (idx == -1) {
        cout << "Scale with id=" << id << " not found.\n";
        return;
    }

    for (const string& field : fieldsToEdit) {
        if (!scales[idx].editField(field)) {
            cout << "Skipping unknown field: " << field << std::endl;
        }
    }

    cout << "Editing completed.\n";
}

void ScaleManager::selectScale(int scaleId) {
    int idx = findScaleIndexById(scaleId);
    if (idx != -1) {
        selectedScale = &scales[idx];
        cout << "Scale with ID " << scaleId << " selected.\n";
    }
    else {
        selectedScale = nullptr;
        cout << "Scale not found.\n";
    }
}

DigitalScale* ScaleManager::getSelectedScale() const {
    return selectedScale;
}

double ScaleManager::calculateTotalWeighingError() const {
    double sum = 0.0;

    for (int i = 0; i < size; ++i) {
        const DigitalScale& scale = scales[i];
        for (const auto& entry : scale.getWeighingLog()) {
            sum += pow(entry.mass * entry.error, 2);
        }
    }

    return sqrt(sum);
}

int ScaleManager::getTotalWeighings() const {
    int total = 0;
    for (int i = 0; i < size; ++i)
        total += scales[i].getWeighingLog().size();
    return total;
}

void ScaleManager::saveScalesToCSV(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file for writing: " << filename << std::endl;
        return;
    }

    file << "id,weight,min,max,error,unitPrice\n";

    for (ScaleManager::Iterator it = begin(); it != end(); ++it) {
        file << *it; // Використовує operator<<
    }

    file.close();
}

void ScaleManager::loadScalesFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    std::string header;
    std::getline(file, header); // Пропустити заголовок

    DigitalScale scale;
    while (file >> scale) { // Використовує operator>>
        addScale(scale);
    }

    file.close();
}

// ===== Ітератор =====

ScaleManager::Iterator::Iterator(DigitalScale* ptr) : current(ptr) {}

DigitalScale& ScaleManager::Iterator::operator*() {
    return *current;
}

DigitalScale* ScaleManager::Iterator::operator->() {
    return current;
}

ScaleManager::Iterator& ScaleManager::Iterator::operator++() {
    ++current;
    return *this;
}

ScaleManager::Iterator& ScaleManager::Iterator::operator=(const Iterator& other) {
    if (this != &other) {
        current = other.current;
    }
    return *this;
}

bool ScaleManager::Iterator::operator!=(const Iterator& other) {
    return current != other.current;
}

bool ScaleManager::Iterator::operator==(const Iterator& other) {
    return current == other.current;
}

ScaleManager::Iterator ScaleManager::begin() const{
    return Iterator(scales);
}

ScaleManager::Iterator ScaleManager::end() const {
    return Iterator(scales + size);
}