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

    // Overload of operator<< to allow printing the Order objects to streams
    friend ostream& operator<<(ostream& os, const Order& order) {
        return os << "Order {"
                  << "quantity=" << order.quantity
                  << ", price=" << order.price
                  << '}';
    }

    // Getters
    [[nodiscard]] auto getQuantity() const {
        return quantity;
    }

    [[nodiscard]] auto getPrice() const {
        return price;
    }
};
