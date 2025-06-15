#pragma once
#include "DigitalScale.h"
#include <vector>

class ScaleManager {
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
    void displayScales() const;
    void addScale(const DigitalScale& scale);
    void removeScale(size_t index);
    void editScaleById(int id, const std::vector<std::string>& fieldsToEdit);
    void selectScale(int scaleId);
    int findScaleIndexById(int id) const;
    void saveScalesToCSV(const std::string& filename) const;
    void loadScalesFromCSV(const std::string& filename);
    double calculateTotalWeighingError() const;
    DigitalScale* getSelectedScale() const;


    // клас-ітератор для роботи з масивом об'єктів. (вкладений клас)
    class Iterator {
    private:
        DigitalScale* current; // Поточний елемент
    public:
        Iterator(DigitalScale* ptr);   // Конструктор ітератора, приймає вказівник на DigitalScale
        DigitalScale& operator*();     // Оператор розіменування для доступу до об'єкта DigitalScale
        DigitalScale* operator->();    // Оператор доступу до членів об'єкта DigitalScale
        Iterator& operator++(); // Префіксний оператор ++ для переходу до наступного елемента
        Iterator& operator=(const Iterator& other);
        bool operator!=(const Iterator& other);
        bool operator==(const Iterator& other);
    };

    // метод для отримання початку масиву об'єктів.
    Iterator begin() const;
    // метод для отримання кінця масиву об'єктів.
    Iterator end() const;
};
