#pragma once

#include <iostream>

using std::ostream;

class Order {
private:
    uint quantity;
    double price;

public:
    Order(const uint quantity, const double price):
        quantity(quantity),
        price(price) {
    }

    ~Order() = default;

    friend ostream& operator<<(ostream& os, const Order& order) {
        return os << "Order {"
                  << "quantity=" << order.quantity
                  << ", price=" << order.price
                  << '}';
    }

    auto getQuantity() const {
        return quantity;
    }

    auto getPrice() const {
        return price;
    }
};
