#include "item.cpp"

class Shelf {
    Item item;
    int quantity;
public:
    Shelf() { }
    ~Shelf() { }

    Item getItem() { return item; }
    int getQuantity() { return quantity; }
    void setItem(Item newItem) { item = newItem; }
    void setQuantity(int newQuantity) { quantity = newQuantity; }
    void decQuantity() { quantity--; }
    void incQuantity() { quantity++; }
};
