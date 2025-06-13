#pragma once
#include "AbstractScaleManager.h"
#include <vector>

class ScaleManager : public AbstractScaleManager {
private:
    DigitalScale* scales;
    int size;
    int capacity;
    int nextScaleId = 1;
    DigitalScale* selectedScale = nullptr;

    void resize();

public:
    ScaleManager();
    ~ScaleManager();

    // Основна логіка
    void displayScales() const override;
    void addScale(const DigitalScale& scale) override;
    void removeScale(size_t index) override;
    void editScaleById(int id, const std::vector<std::string>& fieldsToEdit) override;
    void selectScale(int scaleId) override;
    int findScaleIndexById(int id) const override;
    void saveScalesToCSV(const std::string& filename) const override;
    void loadScalesFromCSV(const std::string& filename) override;
    double calculateTotalWeighingError() const override;
    DigitalScale* getSelectedScale() const override;

    // Ітератор
    class ScaleIterator : public AbstractScaleManager::Iterator {
    private:
        DigitalScale* current;
    public:
        ScaleIterator(DigitalScale* ptr);
        DigitalScale& operator*() override;
        ScaleIterator& operator++() override;
        bool operator!=(const Iterator& other) const override;

        bool operator==(const Iterator& other) const { return !(*this != other); }
    };

    Iterator* begin() const override;
    Iterator* end() const override;
};
