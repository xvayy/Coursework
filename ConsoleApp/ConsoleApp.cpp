#include "PackingWorkshop.h"
#include "ScaleManager.h"
#include "RealNumber.h"
#include <iostream>
#include <limits>
#include <sstream>


using namespace std;

void testRealNumber() {
    try
    {
        RealNumber r;
        r.setMaxRange(15.5);
        r.setMinRange(1);
        r.setValue(12.5);

        RealNumber b(10.2, 0, 11);

        cout << "Value r: " << r.getValue() << endl;
        cout << "Max Range r: " << r.getMaxRange() << endl;
        cout << "Min Range r: " << r.getMinRange() << endl;
        cout << "Value b: " << b.getValue() << endl;
        cout << "Max Range b: " << b.getMaxRange() << endl;
        cout << "Min Range b: " << b.getMinRange() << endl;

        
		RealNumber a = r + b;
		RealNumber f = r - b;
        cout << "----------------------------------------------\n";

		cout << "\nAddition r+b: " << a << endl;
        cout << "Max Range a: " << a.getMaxRange() << endl;
        cout << "Min Range a: " << a.getMinRange() << endl;
        cout << "----------------------------------------------\n";

        cout << "\nSubtraction r-b: " << f << endl;
        cout << "Max Range f: " << f.getMaxRange() << endl;
        cout << "Min Range f: " << f.getMinRange() << endl;

        cout << "----------------------------------------------\n";

		cout << "Multiplying" << endl;
		RealNumber c = r * b;
		cout << "Multiplication r*b: " << c << endl;
		cout << "Max Range c: " << c.getMaxRange() << endl;
		cout << "Min Range c: " << c.getMinRange() << endl;
		cout << "----------------------------------------------\n";

		cout << "Dividing" << endl;
		RealNumber d = b / r;
		cout << "Division b/r: " << d << endl;
		cout << "Max Range d: " << d.getMaxRange() << endl;
		cout << "Min Range d: " << d.getMinRange() << endl;

        cout << "----------------------------------------------\n";
        cout << "Integer part " << r << endl;
		cout << "Integer part of r: " << r[0] << endl;


        cout << "----------------------------------------------\n";
        cout << "Fractional part " << r.getValue() << endl;
		cout << "Fractional part of r: " << r() << endl;

        cout << "----------------------------------------------\n";
		cout << "Check input: " << endl;
		RealNumber inputNumber;
		cout << "Enter a real number: ";
		cin >> inputNumber;
		cout << "You entered: " << inputNumber << endl;
		cout << "Max Range: " << inputNumber.getMaxRange() << endl;
		cout << "Min Range: " << inputNumber.getMinRange() << endl;


		cout << "----------------------------------------------\n";
		cout << "Check assignment: " << endl;
		RealNumber assignedNumber;
		assignedNumber = r;
		cout << "Assigned number: " << assignedNumber << endl;
        cout << "R value after assignment:" << r << endl;
		cout << "Max Range of assigned number: " << assignedNumber.getMaxRange() << endl;
		cout << "Min Range of assigned number: " << assignedNumber.getMinRange() << endl;


    	cout << "----------------------------------------------\n";
		cout << "Check move assignment: " << endl;
        cout << "Address of" << &r << endl;
		RealNumber movedNumber = std::move(r);
		cout << "Address of movedNumber: " << &movedNumber << endl;
		cout << "Address of r after move: " << &r << endl;
        cout << "R value after moving:" << r << endl;
		cout << "Moved number: " << movedNumber << endl;
		cout << "Max Range of moved number: " << movedNumber.getMaxRange() << endl;
		cout << "Min Range of moved number: " << movedNumber.getMinRange() << endl;


		d.print();


        cout << "----------------------------------------------\n";
        cout << "Demo run-time polymorphism\n";
        RealNumber real(5.5, 0.0, 10.0);
        Number* numPtr = &real;
		numPtr->print(); // Виклик методу через вказівник на намбер

		Number *rtpol = new RealNumber(3.14, 0.0, 5.0);
		rtpol->print(); 
    }
    catch (const exception& e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}

void testDigitalScale(){
	try
	{
        DigitalScale dg;
		dg.setWeight(50.0);
        cout << endl << dg.getWeight();


		DigitalScale arr[] = {
			DigitalScale(0,99.0, 0.01, 100.0, 0.05, 100.0),
			DigitalScale(1,0.0, 0.02, 150.0, 0.03, 150.0)
		};

        for (int i = 0; i < 2; i++) {
			cout << "\nScale " << i + 1 << ":\n";
			cout << "Weight: " << arr[i].getWeight() << " kg\n";
			cout << "Weighing Error: " << arr[i].getWeighingError() << " kg\n";
			cout << "Unit Price: " << arr[i].getUnitPrice() << " UAH/kg\n";
			cout << "Total Price: " << arr[i].calculateTotalPrice() << " UAH\n";
			cout << "Min Weight: " << arr[i].getMinWeight() << " kg\n";
			cout << "Max Weight: " << arr[i].getMaxWeight() << " kg\n";
        }

		cout << "----------------------------------------------\n";

		dg.addWeight(49);
		cout << endl << dg.getWeight();
        dg.subtractWeight(40);
        cout << endl << dg.getWeight() << endl;
        dg.setUnitPrice(25.5);
		cout << "Price per kg: " << dg.getUnitPrice() << " UAH/kg" << endl;
		cout << "Price: " << dg.calculateTotalPrice() << " UAH for " << dg.getWeight() << "kg" << endl;
        dg.info();
		cout << "----------------------------------------------\n";
        DigitalScale dg2;
        cout << dg2;

		cin >> dg2;
		cout << dg2;
	}
	catch (const exception& e)
	{
        cerr << "Error: " << e.what() << endl;
	}
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void scalesMenu(AbstractScaleManager& scaleManager) {
    while (true) {
        cout << "\n--- Digital Scales ---\n";
        scaleManager.displayScales();

        cout << "\nChoose an action:\n";
        cout << "1. Add new scale\n";
        cout << "2. Remove scale\n";
        cout << "3. Edit scale\n";
        cout << "4. Return to main menu\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1: {
            DigitalScale scale;
            cin >> scale;
            scaleManager.addScale(scale);
            cout << "Scale added successfully.\n";
            scaleManager.saveScalesToCSV("scales.csv");
            break;
        }
        case 2: {
            int id;
			scaleManager.displayScales();
            cout << "Enter ID of scale to remove: ";
            cin >> id;
            clearInputBuffer();
            int index = scaleManager.findScaleIndexById(id);
            if (index != -1) {
                scaleManager.removeScale(index);
                cout << "Scale removed.\n";
                scaleManager.saveScalesToCSV("scales.csv");
            }
            else {
                cout << "Scale not found.\n";
            }
            break;
        }
        case 3: {
            int id;
            clearInputBuffer();
            scaleManager.displayScales();
            cout << "Enter ID of scale to edit: ";
            cin >> id;
            cin.ignore();

            vector<string> fields;
            cout << "Enter fields to edit (min max error price), separated by space: ";
            string input;
            getline(cin, input);
            istringstream iss(input);
            string field;
            while (iss >> field) {
                fields.push_back(field);
            }

            scaleManager.editScaleById(id, fields);
            scaleManager.saveScalesToCSV("scales.csv");
            break;
        }
        case 4:
            return;
        default:
            cout << "Invalid option. Please try again.\n";
            break;
        }
    }
}

void packingMenu(PackingWorkshop& pw, AbstractScaleManager& scaleManager) {
    int scaleId;
    scaleManager.displayScales();
    cout << "\n=== Packaging Process ===\n";
    cout << "Enter scale ID to use: ";
    cin >> scaleId;
    scaleManager.selectScale(scaleId);
    pw.displayProductInfo();

    cout << "Enter amount to weigh (kg): ";
    double weight;
    cin >> weight;

    clearInputBuffer();
    if (pw.weighProduct(weight)) {
        while (true) {
    		cout << "[a]dd more, [s]ubtract, [p]ack, [c]ancel: ";
            string input;
            getline(cin, input);

            if (input.empty()) continue;
			if (input.size() > 1) {
				cout << "Invalid input. Please enter a single character.\n";
				continue;
			}
            char action = tolower(input[0]);

            if (action == 'a') {
                cout << "Enter amount to add: ";
                cin >> weight;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                pw.weighProduct(weight);
                if (pw.getSelectedScale())
                    cout << "Current weight on scale: " << pw.getSelectedScale()->getMeasuredWeight() << " kg\n";
            }
            else if (action == 's') {
                cout << "Enter amount to subtract: ";
                cin >> weight;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                if (pw.getSelectedScale()) {
                    pw.getSelectedScale()->subtractWeight(weight);
                    pw.setProductQuantity(pw.getProductQuantity() + weight);
                    cout << "Weight removed.\n";
                    cout << "Current weight on scale: " << pw.getSelectedScale()->getMeasuredWeight() << " kg\n";
                }
                else {
                    cout << "No scale selected.\n";
                }
            }
            else if (action == 'p') {
                pw.packProduct();
                break;
            }
            else if (action == 'c') {
                break;
            }
            else {
                cout << "Invalid choice. Please try again.\n";
            }
        }
    }
}

void polyDemo() {
    cout << "\n==============================\n";
    cout << "Demo run-time polymorphism\n";
    cout << "==============================\n";
    Number* numbers[2];
    numbers[0] = new RealNumber(2.71, 0.0, 10.0);
    numbers[1] = new Number(3.14);

    for (int i = 0; i < 2; ++i) {
        cout << "Object " << i + 1 << ": ";
        numbers[i]->print();
        delete numbers[i];
        cout << endl;
    }
}

int main() {
    try {
        ScaleManager scaleManager;
        scaleManager.loadScalesFromCSV("scales.csv");
        PackingWorkshop workshop(&scaleManager, "Meat", "chicken", 578, 80, 10, 0);

        while (true) {
            cout << "\n=== Main Menu ===\n";
            cout << "1. Manage digital scales\n";
            cout << "2. Start packaging process\n";
            cout << "3. Calculate total weighing error\n";
            cout << "4. Calculate total price\n";
            cout << "5. Demo run-time polymorphism\n";
            cout << "6. Exit\n";
            cout << "Enter your choice: ";

            int mainChoice;
            cin >> mainChoice;
            clearInputBuffer();

            switch (mainChoice) {
            case 1:
                scalesMenu(scaleManager);
                break;
            case 2:
                packingMenu(workshop, scaleManager);
                break;
            case 3:
                cout << "Total weighing error: " << scaleManager.calculateTotalWeighingError() << " kg\n";
                break;
            case 4:
                cout << "Total price: " << workshop.getTotalPrice() << " UAH\n";
                break;
            case 5:
                polyDemo();
                break;
            case 6:
                scaleManager.saveScalesToCSV("scales.csv");
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid option. Please try again.\n";
                break;
            }
        }
    }
    catch (const exception& ex) {
        cerr << "Fatal error: " << ex.what() << endl;
    }

    return 0;
}