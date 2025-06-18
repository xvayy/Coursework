#include "PackingWorkshop.h"
#include "ScaleManager.h"
#include "RealNumber.h"
#include <iostream>
#include <limits>
#include <sstream>


using namespace std;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void scalesMenu(ScaleManager& scaleManager) {
    while (true) {
        cout << "\n========== Digital Scales ==========\n";
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
            scaleManager.displayScales();
            cout << "Enter ID of scale to edit: ";
            cin >> id;
            clearInputBuffer();

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

void packingMenu(PackingWorkshop& pw, ScaleManager& scaleManager) {
    int scaleId;
    scaleManager.displayScales();
    cout << "\n=== Packaging Process ===\n";
    cout << "Enter scale ID to use: ";
    cin >> scaleId;
    scaleManager.selectScale(scaleId);
    pw.setCurrentScale(scaleManager.getSelectedScale());
    pw.displayInfo();

    cout << "Enter amount to weigh (kg): ";
    double weight;
    cin >> weight;

    clearInputBuffer();
    if (pw.startWeighing(weight)) {
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
				clearInputBuffer();
                pw.startWeighing(weight);
                if (pw.getCurrentScale())
                    cout << "Current weight on scale: " << pw.getCurrentScale()->getMeasuredWeight() << " kg\n";
            }
            else if (action == 's') {
                cout << "Enter amount to subtract: ";
                cin >> weight;
				clearInputBuffer();
                if (pw.getCurrentScale()) {
                    pw.getCurrentScale()->subtractWeight(weight);
                    pw.setProductQuantity(pw.getProductQuantity() + weight);
                    cout << "Weight removed.\n";
                    cout << "Current weight on scale: " << pw.getCurrentScale()->getMeasuredWeight() << " kg\n";
                }
                else {
                    cout << "No scale selected.\n";
                }
            }
            else if (action == 'p') {
                pw.startPacking();
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
    system("color F0");
    try {
        ScaleManager scaleManager;
        scaleManager.loadScalesFromCSV("scales.csv");
		Product product("Chicken", 1346, 15, 10); 
        PackingWorkshop workshop("Meat", product);

        while (true) {
            cout << "\n============ Main Menu ============\n";
            cout << "1. Manage digital scales\n";
            cout << "2. Start packaging process\n";
            cout << "3. Calculate total weighing error\n";
            cout << "4. Calculate total price\n";
            cout << "5. Demo run-time polymorphism\n";
            cout << "6. Exit\n";
            cout << "===================================\n";
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
				cout << "Number of weighings: " << scaleManager.getTotalWeighings() << endl;
                cout << "Total weighing error: " << scaleManager.calculateTotalWeighingError() << " kg\n";
                break;
            case 4:
				cout << "\nTotal packages packed: " << workshop.getPackageCount() << endl;
                cout << "Total cost price: " << workshop.getTotalPrice() << " UAH\n";
                cout << "Total sale price (with markup): " << workshop.getTotalPackagePrice() << " UAH\n";
                cout << "Profit: " << workshop.getTotalPackagePrice() - workshop.getTotalPrice() << " UAH\n";

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