using namespace std;

class Item { 
	string Name;
	double Price;
public:
	Item(string name, double price) {
		Name = name;
		Price = price;
	}
    Item() { }
	~Item() { }

	string getName() { return Name; }
	double getPrice() { return Price; }
	void setName(string newName) { Name = newName; }
	void setPrice(double newPrice) { Price = newPrice; }

};
