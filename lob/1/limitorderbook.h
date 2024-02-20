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
    using BuyOrderMap = map<const double, size_t>;
    using SellOrderMap = map<const double, size_t>;

    string symbol;
    BuyOrderMap buyOrders;
    SellOrderMap sellOrders;

public:
    LimitOrderBook(string symbol) :
        symbol(move(symbol)),
        buyOrders(BuyOrderMap()),
        sellOrders(SellOrderMap())
    {
        // log("LimitOrderBook:ctor");
    }

    ~LimitOrderBook()
    {
        // log("LimitOrderBook:dtor");
    }

    void insert(const Order& order, const string& side)
    {
        ostringstream ss;
        ss << "Inserting from thread: " << this_thread::get_id();
        const string message = ss.str();
        // log(message);
        
        if (order.getQuantity() <= 0) {
            throw invalid_argument("Order quantity must be positive");
        }

        if (side == "BUY") {
        } else if (side == "SELL") {
        } else {
            throw invalid_argument("Invalid order side");
        }
    }

    void print() const {
        std::cout << "Order Book for " << symbol << std::endl;
        std::cout << "Spread: " << getSpread() << std::endl;
        std::cout << "Count Buy Orders: " << buyOrders.size() << std::endl;
        printOrders(buyOrders);
        std::cout << "Count Sell Orders: " << sellOrders.size() << std::endl;
        printOrders(sellOrders);
    }
    
    double getSpread() const {
        if (buyOrders.empty() || sellOrders.empty()) {
            // If there are no buy or sell orders, the spread cannot be computed.
            throw runtime_error("Cannot compute spread with empty buy or sell orders");
        }
    
        return 0;
    }

private:
    template<typename OrderMap>
    void printOrders(const OrderMap& orders) const {
        for (const auto& order : orders) {
            std::cout << "Price: " << order.first << ", Quantity: " << order.second << std::endl;
        }
    }
};
