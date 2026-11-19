#include <iostream>
#include <exception>
#include "Order.hpp"

int main() {
    Order buyOrder(1,100,Side::Buy,OrderType::Limit,10,1);
    std::cout<<"Initial Price:"<< buyOrder.getPrice()<< '\n';

    std::cout<<" ,Order ID: " << buyOrder.getId()
    <<" ,Amount left: " << buyOrder.getRemainingQuantity()<< '\n';

    buyOrder.fill(100);
    std::cout<< "After transaction: " << buyOrder.getRemainingQuantity()
    << " Completed?: " << buyOrder.isFilled() << '\n';

    try {
        buyOrder.fill(1000);
    } catch (const std::exception& e) {
        std::cout << "Caught error: " << e.what() << '\n';
    }

    return 0;

}