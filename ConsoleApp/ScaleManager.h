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

    // ������� �����
    void displayScales() const;
    void addScale(const DigitalScale& scale);
    void removeScale(int index);
    void editScaleById(int id, const vector<string>& fieldsToEdit);
    void selectScale(int scaleId);
    int findScaleIndexById(int id) const;
    void saveScalesToCSV(const string& filename) const;
    void loadScalesFromCSV(const string& filename);
    double calculateTotalWeighingError() const;
	int getTotalWeighings() const;
    DigitalScale* getSelectedScale() const;


    // ����-�������� ��� ������ � ������� ��'����. (��������� ����)
    class Iterator {
    private:
        DigitalScale* current; // �������� �������
    public:
        Iterator(DigitalScale* ptr);   // ����������� ���������, ������ �������� �� DigitalScale
        DigitalScale& operator*();     // �������� ������������ ��� ������� �� ��'���� DigitalScale
        DigitalScale* operator->();    // �������� ������� �� ����� ��'���� DigitalScale
        Iterator& operator++(); // ���������� �������� ++ ��� �������� �� ���������� ��������
        Iterator& operator=(const Iterator& other);
        bool operator!=(const Iterator& other);
        bool operator==(const Iterator& other);
    };

    // ����� ��� ��������� ������� ������ ��'����.
    Iterator begin() const;
    // ����� ��� ��������� ���� ������ ��'����.
    Iterator end() const;
};
