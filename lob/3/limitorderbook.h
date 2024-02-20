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

template<typename Allocator = std::allocator<std::pair<const double, size_t>>>
class LimitOrderBook {
private:
    using BuyOrderMap = std::map<const double, size_t, std::greater<>, Allocator>;
    using SellOrderMap = std::map<const double, size_t, std::less<>, Allocator>;

    std::string symbol;
    BuyOrderMap buyOrders;
    SellOrderMap sellOrders;

public:
    LimitOrderBook(std::string symbol, Allocator& alloc = Allocator()) :
        symbol(std::move(symbol)),
        buyOrders(BuyOrderMap(std::greater<>(), alloc)),
        sellOrders(SellOrderMap(std::less<>(), alloc))
    {
    }

    ~LimitOrderBook()
    {
    }

    void insert(const Order& order, const std::string& side)
    {
        std::ostringstream ss;
        ss << "Inserting from thread: " << std::this_thread::get_id();
        const std::string message = ss.str();
        //log(message);

        if (order.getQuantity() <= 0) {
            throw std::invalid_argument("Order quantity must be positive");
        }

        if (side == "BUY") {
            buyOrders[order.getPrice()] += order.getQuantity();
        } else if (side == "SELL") {
            sellOrders[order.getPrice()] += order.getQuantity();
        } else {
            throw std::invalid_argument("Invalid order side");
        }
    }

    void print() const {
        std::cout << "Buy Orders: " << buyOrders.size() << std::endl;
        std::cout << "Sell Orders: " << sellOrders.size() << std::endl;
    }
};
