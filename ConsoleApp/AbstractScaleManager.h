#pragma once
#include "DigitalScale.h"
#include <string>
#include <vector>

class AbstractScaleManager {
public:
    virtual ~AbstractScaleManager() = default;

    virtual void displayScales() const = 0;
    virtual void addScale(const DigitalScale& scale) = 0;
    virtual void removeScale(size_t index) = 0;
    virtual void editScaleById(int id, const std::vector<std::string>& fieldsToEdit) = 0;
    virtual void selectScale(int scaleId) = 0;
    virtual int findScaleIndexById(int id) const = 0;

    virtual void saveScalesToCSV(const std::string& filename) const = 0;
    virtual void loadScalesFromCSV(const std::string& filename) = 0;

    virtual double calculateTotalWeighingError() const = 0;
    virtual DigitalScale* getSelectedScale() const = 0;


    class Iterator {
    public:
        virtual ~Iterator() = default;
        virtual DigitalScale& operator*() = 0;
        virtual Iterator& operator++() = 0;
        virtual bool operator!=(const Iterator& other) const = 0;
    };

    virtual Iterator* begin() const = 0;
    virtual Iterator* end() const = 0;
};
