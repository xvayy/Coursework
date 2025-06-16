#include "ScaleManager.h"
#include <iostream>
#include <fstream>
#include <cmath>

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

void ScaleManager::removeScale(size_t index) {
    if (index >= size) {
        throw out_of_range("Invalid scale index.");
    }
    for (size_t i = index; i < size - 1; ++i) {
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


void ScaleManager::editScaleById(int id, const std::vector<std::string>& fieldsToEdit) {
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
    ScaleManager::Iterator it = begin();
    ScaleManager::Iterator itEnd = end();

    for (; it != itEnd; ++it) {
        const DigitalScale& scale = (*it);
        for (const auto& entry : scale.getWeighingLog()) {
            sum += std::pow(entry.mass * entry.error, 2);
        }
    }
    return std::sqrt(sum);
}



void ScaleManager::saveScalesToCSV(const std::string& filename) const {
    std::ofstream file(filename);
    file << "id,weight,min,max,error,unitPrice\n";

    ScaleManager::Iterator it = begin();
    ScaleManager::Iterator itEnd = end();

    for (; it != itEnd; ++it) {
        file << (*it).toCSVRow();
    }
}


void ScaleManager::loadScalesFromCSV(const std::string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        DigitalScale scale;
        scale.fromCSVRow(line);
        addScale(scale);
    }
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