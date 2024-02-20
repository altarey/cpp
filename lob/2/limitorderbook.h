#pragma once

#include <map>
#include <string>
#include <functional>
#include <utility>
#include <iostream>
#include <shared_mutex>
#include <thread>
#include <sstream>

#include "log.h"  
#include "order.h"

using namespace std;

template<typename Allocator = allocator<pair<const double, size_t>>>
class LimitOrderBook {
private:
    using BuyOrderMap = map<const double, size_t, less<>, Allocator>;
    using SellOrderMap = map<const double, size_t, less<>, Allocator>;

    string symbol;
    BuyOrderMap buyOrders;
    SellOrderMap sellOrders;

public:
    LimitOrderBook(string symbol, Allocator& alloc = Allocator()) :
        symbol(move(symbol)),
        buyOrders(BuyOrderMap(alloc)),
        sellOrders(SellOrderMap(alloc))
    {
        // log("LimitOrderBook:ctor");
    }

    ~LimitOrderBook()
    {
        // log("LimitOrderBook:dtor");
    }

    void insert(const Order& order, const string& side)
    {
        if (order.getQuantity() <= 0) {
            throw invalid_argument("Order quantity must be positive");
        }

        if (side == "BUY") {
            buyOrders[order.getPrice()] += order.getQuantity();
        } else if (side == "SELL") {
            sellOrders[order.getPrice()] += order.getQuantity();
        } else {
            throw invalid_argument("Invalid order side");
        }
    }

    void print() const {
        std::cout << "Count Buy Orders: " << buyOrders.size() << std::endl;
        std::cout << "Count Sell Orders: " << sellOrders.size() << std::endl;
    }
};
