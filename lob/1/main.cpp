#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <execution>
#include <future>

#include "order.h"
#include "limitorderbook.h"

using namespace std;

int main() {
    LimitOrderBook<pair<const double, size_t>> orderBook("AAPL");

    constexpr auto N = 6; // Number of orders

    // Generate orders
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> quantityDistr(1, 100);
    uniform_real_distribution<> priceDistr_Buy(100.0, 150.0);
    uniform_real_distribution<> priceDistr_Sell(152.0, 200.0);

    for (int i = 0; i < N; ++i) {
        auto quantity = quantityDistr(gen);
        auto price_buy = priceDistr_Buy(gen);
        auto price_sell = priceDistr_Sell(gen);
        if (i % 2 == 0) {
            orderBook.insert(Order(quantity, price_buy), "BUY");
        } else {
            orderBook.insert(Order(quantity, price_sell), "SELL");
        }
    }

    orderBook.print();

    return 0;
}
