#ifndef PACKAGINGWORKSHOP_H
#define PACKAGINGWORKSHOP_H

#include "DigitalScale.h"

// ����-�������� ��� ������ ������ DigitalScale
class ScaleIterator {
private:
    DigitalScale* ptr; // �������� �� �������� �������
    int size;          // ����� ������
    int index;         // �������� ������

public:
    ScaleIterator(DigitalScale* start, int size, int index = 0);

    DigitalScale& operator*();
    ScaleIterator& operator++();
    bool operator!=(const ScaleIterator& other) const;
};

// ���� ����������� ���
class PackagingWorkshop {
private:
    DigitalScale* scales; // ��������� ����� ���
    int capacity;         // ����������� ������� ������
    int count;            // ������� ������� ��������
    double targetWeight;  // �������� ���� ��� ���������

public:
    PackagingWorkshop(double target = 0.0, int initialCapacity = 10);
    ~PackagingWorkshop();

    void addScale(const DigitalScale& scale);
    void packageProduct();
    double calculateTotalError() const;
    double calculateTotalPrice() const;

    // ������ ��� ���������
    ScaleIterator begin();
    ScaleIterator end();
};

#endif // PACKAGINGWORKSHOP_H