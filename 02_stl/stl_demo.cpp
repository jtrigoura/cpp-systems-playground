#include <iostream>
#include <vector>
#include <map>
#include <deque>

struct Order {
    int id;
    double price;
    int qty;
};

int main() {
    std::vector<Order> orders;
    orders.push_back({1, 100.5, 10});
    orders.push_back({2, 101.0, 5});

    std::map<double, std::deque<Order>> order_book;

    for (const Order& o : orders) {
        order_book[o.price].push_back(o);
    }

    for (const auto& [price, queue] : order_book) {
        std::cout << "Price: " << price << "\n";
        for (const Order& o : queue) {
            std::cout << "  Order " << o.id << " qty=" << o.qty << "\n";
        }
    }
}
