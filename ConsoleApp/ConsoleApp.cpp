#include "PackingWorkshop.h"
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

// Функція для очищення вводу
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/*
void menu(PackingWorkshop& pws) {
    while (true) {
        cout << "\n=== Packing Workshop Menu ===\n";
        cout << "1. View list of available scales\n";
        cout << "2. Add product (append to CSV)\n";
        cout << "3. Remove product by name\n";
        cout << "4. Add quantity to product by name\n";
        cout << "5. Pack a product (simulate)\n";
        cout << "7. Add scale\n";
        cout << "8. Remove scale\n";

        cout << "9. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        clearInputBuffer();

        try {
            switch (choice) {
            case 1:
                pws.displayScales();
                break;

            case 2:
                pws.saveProductsToCSV();
                break;

            case 3: {
                string name;
                cout << "Enter product name to remove: ";
                getline(cin, name);
                pws.removeProduct(name);
                break;
            }

            case 4: {
                string name;
                double quantity;
                cout << "Enter product name: ";
                getline(cin, name);
                cout << "Enter quantity to add (kg): ";
                cin >> quantity;
                clearInputBuffer();
                pws.addProductQuantity(name, quantity);
                break;
            }

            case 5:
                pws.packProduct();
                break;

            case 6:
                pws.loadProductsFromCSV();
                break;

            case 7: {
                DigitalScale newScale;
                pws.addScale(newScale);
            		break;
            }
            case 8: {
                int index;
                pws.displayScales();
                cout << "Enter scale index to remove: ";
                cin >> index;
                pws.removeScale(index - 1);
                break;
            }
            case 9:
                cout << "Exiting program.\n";
                return;

            default:
                cout << "Invalid choice. Please try again.\n";
            }
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            clearInputBuffer();
        }
    }
}
*/

void scalesMenu(PackingWorkshop& workshop) {
    while (true) {
        cout << "\n--- Digital Scales ---\n";
        workshop.displayScales();

        cout << "\nChoose an action:\n";
        cout << "1. Add new scale\n";
        cout << "2. Remove scale\n";
        cout << "3. Edit scale\n";
        cout << "4. Return to main menu\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            DigitalScale scale;
            cin >> scale;
            workshop.addScale(scale);
            cout << "Scale added successfully.\n";
            workshop.saveScalesToCSV("scales.csv");
            break;
        }
        case 2: {
            int id;
            cout << "Enter ID of scale to remove: ";
            cin >> id;
            int index = workshop.findScaleIndexById(id);
            if (index != -1) {
                workshop.removeScale(index);
                cout << "Scale removed.\n";
                workshop.saveScalesToCSV("scales.csv");
            }
            else {
                cout << "Scale not found.\n";
            }
            break;
        }
        case 3: {
            int id;
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

            workshop.editScaleById(id, fields);
            workshop.saveScalesToCSV("scales.csv");
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

void packingMenu(PackingWorkshop& pw) {
    int scaleId;
    pw.displayScales();
	cout << "\n=== Packaging Process ===\n";
    cout << "Enter scale ID to use: ";
    cin >> scaleId;
    pw.selectScale(scaleId);
    pw.displayProductInfo();
    double weight;
    cout << "Enter amount to weigh (kg): ";
    cin >> weight;

    if (pw.weighProduct(weight)) {
        char action;
        while (true) {
            cout << "[a]dd more, [s]ubtract, [p]ack, [c]ancel: ";
            cin >> action;

            if (action == 'a') {
                cout << "Enter amount to add: "; cin >> weight;
                pw.weighProduct(weight);
                if (pw.getSelectedScale())
                    cout << "Current weight on scale: " << pw.getSelectedScale()->getWeight() << " kg\n";
            }
            else if (action == 's') {
                cout << "Enter amount to subtract: "; cin >> weight;
                if (pw.getSelectedScale()) {
                    pw.getSelectedScale()->subtractWeight(weight);
                    pw.setProductQuantity(pw.getProductQuantity() + weight);
                    cout << "Weight removed.\n";
                    cout << "Current weight on scale: " << pw.getSelectedScale()->getWeight() << " kg\n";
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
        }
    }
}


void polyDemo() {
    cout << "Demo run-time polymorphism\n";
    Number* numbers[2];
    numbers[0] = new RealNumber(2.71, 0.0, 10.0);
    numbers[1] = new RealNumber(3.14, 0.0, 5.0);

    for (int i = 0; i < 2; ++i) {
        cout << "Object " << i + 1 << ": ";
        numbers[i]->print();
        delete numbers[i];
    }
}
int main() {
    try {
        PackingWorkshop workshop("Meat", "chicken", 578, 80, 10, 0);
        workshop.loadScalesFromCSV("scales.csv");

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
            cin.ignore();

            switch (mainChoice) {
            case 1:
                scalesMenu(workshop);
                break;
			case 2:
				packingMenu(workshop);
				break;
			case 3:
				cout << "Total weighing error: " << workshop.calculateTotalWeighingError() << " kg\n";
				break;
            case 4:
                cout << "Total price: " << workshop.getTotalPrice() << " kg\n";
                break;
			case 5:
				polyDemo();
                break;
            case 6:
                workshop.saveScalesToCSV("scales.csv");
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