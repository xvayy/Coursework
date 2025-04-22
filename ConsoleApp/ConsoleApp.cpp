#include "RealNumber.h"
#include "DigitalScale.h"
#include "PackagingWorkshop.h"

int main() {
    try {
        // Створення об'єктів базового класу
        RealNumber num1(5.7);
        RealNumber num2(3.2);

        // Перевірка операторів
        std::cout << "Num1: " << num1 << ", Num2: " << num2 << std::endl;
        std::cout << "Addition: " << (num1 + num2) << std::endl;
        std::cout << "Subtraction: " << (num1 - num2) << std::endl;
        std::cout << "Multiplication: " << (num1 * num2) << std::endl;
        std::cout << "Division: " << (num1 / num2) << std::endl;
        std::cout << "Fractional part of Num1: " << num1() << std::endl;
        std::cout << "Integer part of Num1: " << num1[0] << std::endl;

        // Створення об'єктів похідного класу
        DigitalScale scale1(2.5, 0.02, 10.0); // вага, похибка, ціна за одиницю
        DigitalScale scale2(3.0, 0.01, 12.0);
        DigitalScale scale3(1.8, 0.03, 15.0);

        // Демонстрація поліморфізму
        RealNumber* scales[] = { &scale1, &scale2, &scale3 };
        std::cout << "\nPolymorphic display:\n";
        for (const auto& scale : scales) {
            scale->display();
        }

        // Робота з фасувальним цехом
        PackagingWorkshop workshop(5.0); // цільова вага 5 кг
        workshop.addScale(scale1);
        workshop.addScale(scale2);
        workshop.addScale(scale3);

        std::cout << "\nPackaging workshop results:\n";
        workshop.packageProduct();
        std::cout << "Total error: " << workshop.calculateTotalError() << " kg" << std::endl;
        std::cout << "Total price: " << workshop.calculateTotalPrice() << std::endl;

        // Демонстрація ітератора
        std::cout << "\nIterating through scales using iterator:\n";
        for (ScaleIterator it = workshop.begin(); it != workshop.end(); ++it) {
            (*it).display();
        }
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}