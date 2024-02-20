#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <execution>
#include <future>

#include "order.h"
#include "limitorderbook.h"
#include "cpp_allocator.h"

using namespace std;

int main() {
    CPP_Allocator<pair<const double, size_t>> c_alloc;
    LimitOrderBook<CPP_Allocator<pair<const double, size_t>>> orderBook("AAPL", c_alloc);

    constexpr auto N = 1000; // Number of orders

    vector<Order> buyOrders;
    vector<Order> sellOrders;
    buyOrders.reserve(N / 2);
    sellOrders.reserve(N / 2);

    // Generate orders
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> quantityDistr(1, 100);
    uniform_real_distribution<> priceDistr(100.0, 200.0);

    for (int i = 0; i < N; ++i) {
        auto quantity = quantityDistr(gen);
        auto price = priceDistr(gen);
        if (i % 2 == 0) {
            buyOrders.emplace_back(quantity, price);
        } else {
            sellOrders.emplace_back(quantity, price);
        }
    }

    vector<future<void>> futures;

    for (const auto& order : buyOrders) {
        futures.push_back(async(launch::async, [&orderBook, order] {
            orderBook.insert(order, "BUY");
        }));
    }

    for (const auto& order : sellOrders) {
        futures.push_back(async(launch::async, [&orderBook, order] {
            orderBook.insert(order, "SELL");
        }));
    }

    // Wait for all operations to complete
    for (auto& fut : futures) {
        fut.get();
    }

    orderBook.print();

    return 0;
}
