#include <iostream>
#include <iomanip>

#include "vendingmachine.cpp"
//#include "item.cpp"
//#include "shelf.cpp"

using namespace std;

void printPocket(VendingMachine vm);
void debug(VendingMachine vm);
void printBreak();

enum Option {
    ne,
    del,
    up,
    ct,
    ut,
    Option_Invalid
};

Option resolveOption(string input);

int main() {

	VendingMachine vendingmachine;
	Item chips("Chips", 1.00);
    Item candyBar("Candy Bar", 1.50);
    Item soda("Soda", 2.00);
    
    double wallet = 5.57;
    Item pocket[5];
    int pocketDepth = 0;

    // 5x5 vending machine
	vendingmachine.updateShelf(0, chips, 10);
	vendingmachine.updateShelf(1, candyBar, 5);
	vendingmachine.updateShelf(3, candyBar, 10);
	Item currItem = vendingmachine.getShelfItem(0*0);

    // set vendingmachine till
    vendingmachine.setTill(30.00);

    // Loop start
    bool running = true;
    while (running) {
        string input, choiceName;
        double choicePrice, payedAmt, change;
        int choice;

        printPocket(vendingmachine);

        cout << "WALLET: $" << wallet << endl;
        cout << "ENTER A ITEM LOCATION " << endl;
        cout << "Enter -1 to leave" << endl;
        cin >> input;

        if (input == "-1") { 
            running = false;
            cout << "Goodbye" << endl;
            break;
        }
        if (input == "-69") { 
            debug(vendingmachine);
            continue;
        }
        if (stoi(input) < 0 || stoi(input) > vendingmachine.getSize()) { 
            cout << "INVALID LOCATION" << endl;
            printBreak();
            continue;
        }

        choice = stoi(input);
        Item selectedItem = vendingmachine.getShelfItem(choice);

        printBreak();

        choiceName = selectedItem.getName();
        choicePrice = selectedItem.getPrice();
        cout << choiceName << endl;
        cout << choicePrice << endl;
        cout << "INSERT CASH" << endl;
        cout << "Enter amount of money to pay or 0 to decline." << endl;
        cin >> input;
        payedAmt = stod(input);

        change = vendingmachine.getChange(choicePrice, payedAmt);

        if (change < 0) {
            cout << "INSUFFICIENT FUNDS" << endl;
            continue;
        } 

        cout << "Change: $" << change << endl;
        wallet -= payedAmt;
        wallet += change; 
        pocket[pocketDepth] = selectedItem;
        pocketDepth++;
        vendingmachine.addTill(choicePrice);
        printBreak();
    }

	return 0;
};

void printBreak() {
    cout << "=====================" << endl;
};


void printPocket(VendingMachine vm) {
    for( int i = 0; i < vm.getSize(); i++ ) {
        cout << i << ": " << vm.getShelfItem(i).getName() << endl;
    }
    cout << "=====================" << endl;
};

void debug(VendingMachine vm) { 
    string input, option;
    cout << "ne to enter a item" << endl;
    cout << "del: to remove a item" << endl;
    cout << "up: to update a item quanttiy" << endl;
    cout << "ct: to check till" << endl;
    cout << "ut: to update till" << endl;
    cin >> input;
    option = input;

    string name;
    double price;
    int quant, shelf;
    
    switch (resolveOption(option)) { 
        case ne: {
            cout << "Enter item name" << endl;
            cin >> name;
            cout << "Enter item price" << endl;
            cin >> input;
            price = stod(input);
            cout << "Enter quantity" << endl;
            cin >> input;
            quant = stoi(input);
            cout << "Enter shelf" << endl;
            cin >> input;
            shelf = stoi(input);
            cout << shelf << endl;
            Item newItem(name, price);
            vm.updateShelf(shelf, newItem, quant);
            break;
        };
        case del: {
            cout << "Enter shelf number" << endl; cin >> input;
            shelf = stoi(input);
            vm.removeShelf(shelf);
            break;
        };
        case up: {
            cout << "Enter shelf number" << endl;
            cin >> input;
            shelf = stoi(input);
            cout << "Enter quantity" << endl;
            cin >> input;
            quant = stoi(input);
            break;
        };
        default:
            cout << "INVALID OPTION" << endl;
            break;
    }
};

Option resolveOption(string input) {
    if (input == "ne") return ne;
    if (input == "del") return del;
    if (input == "up") return up;
    if (input == "ct") return ct;
    if (input == "ut") return ut;
    return Option_Invalid;
};
