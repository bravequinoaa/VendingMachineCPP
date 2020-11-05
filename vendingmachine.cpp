#include "shelf.cpp"
//#include "item.cpp"


class VendingMachine {
    double til;
	Shelf shelves[5*5];
    
public:
	VendingMachine() { }
	~VendingMachine() { }

	Item getShelfItem(int shelf) { return shelves[shelf].getItem();  }
	int getShelfQuantity(int shelf) { return shelves[shelf].getQuantity(); }
    double getTil() { return til; }

    void setTil(double newTil) { til = newTil; }
    void addTil(double amount) { til+=amount; }
    void minTil(double amount) { til-=amount; }

	void updateShelf(int shelf, Item item, int quantity) {
		Shelf newShelf;
		newShelf.setItem(item);
		newShelf.setQuantity(quantity);
		shelves[shelf] = newShelf;
	}

    void removeShelf(int s) {
        shelves[s].getItem().setName("");
        shelves[s].getItem().setPrice(0);
    }

    double getChange(double owed, double payed) { return payed - owed; }

    int getSize() {
        return sizeof(shelves) / sizeof(Shelf);
    }

};

