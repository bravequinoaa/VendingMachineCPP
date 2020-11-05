#include <iostream>
#include <iomanip>

#include "vendingmachine.cpp"
//#include "item.cpp"
//#include "shelf.cpp"

using namespace std;

void printPocket(VendingMachine vm);
void debug(VendingMachine vm);
constexpr unsigned int str2int(const char* str, int h = 0);

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
	cout << "Shelf 0x0 contains: " << currItem.getName() << endl << endl;

    vendingmachine.setTil(30.00);
    cout << fixed << setprecision(2);
    cout << "$" << vendingmachine.getTil() << endl;
    vendingmachine.addTil(5.00);
    vendingmachine.minTil(1.50);
    cout << "$" << vendingmachine.getTil() << endl;


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
            break;
        }
        if (input == "-69") { 
            debug(vendingmachine);
            continue;
        }

        choice = stoi(input);
        Item selectedItem = vendingmachine.getShelfItem(choice);
        cout << selectedItem.getName().length() << endl;

        if (selectedItem.getName().length() <= 0) {
           cout << "INVALID LOCATION" << endl; 
           continue; 
        }
        cout << "=====================" << endl;
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
        vendingmachine.addTil(choicePrice);
    }

	return 0;
};


void printPocket(VendingMachine vm) {
    for( int i = 0; i < vm.getSize(); i++ ) {
        cout << i << ": " << vm.getShelfItem(i).getName() << endl;
    }
    cout << "=====================" << endl;
};

void debug(VendingMachine vm) { 
    string input, option;
    cout << "new to enter a item" << endl;
    cout << "del: to remove a item" << endl;
    cout << "up: to update a item quanttiy" << endl;
    cout << "ct: to check til" << endl;
    cout << "ut: to update til" << endl;
    cin >> input;
    option = input;

    string name;
    double price;
    int quant, shelf;
    
    switch (str2int(option)) { 
        case str2int("new"): {
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
            Item newItem(name, price);
            vm.updateShelf(shelf, newItem, quant);
            break;
        }
        case str2int("del"): {
            cout << "Enter shelf number" << endl; cin >> input;
            shelf = stoi(input);
            vm.removeShelf(shelf);
            break;
        }
        case str2int("up"): {
            cout << "Enter shelf number" << endl;
            cin >> input;
            shelf = stoi(input);
            cout << "Enter quantity" << endl;
            cin >> input;
            quant = stoi(shelf);
            break;
        }
        default:
            cout << "INVALID OPTION" << endl;
    }
}

constexpr unsigned int str2int(string str, int h = 0) {
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}
