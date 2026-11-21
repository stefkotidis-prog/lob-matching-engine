#include <cassert>
#include <iostream>
#include "OrderBook.hpp"

void printTrades(const std::vector<Trade>& trades) {
    for (const auto& t : trades) {
        std::cout << "Trade: buy=" << t.buyOrderId
                  << " sell=" << t.sellOrderId
                  << " qty=" << t.quantity
                  << " price=" << t.price
                  << " ts=" << t.timestamp << '\n';
    }
}

int main() {
    OrderBook book;

    assert(!book.getBestBid().has_value());
    assert(!book.getBestAsk().has_value());
    assert(book.getOrderCount() == 0);

    book.addOrder(Order(1, 100, Side::Sell, OrderType::Limit, 105, 1));
    book.addOrder(Order(2, 50, Side::Sell, OrderType::Limit, 105, 2));
    book.addOrder(Order(3, 80, Side::Sell, OrderType::Limit, 110, 3));
    book.addOrder(Order(4, 60, Side::Buy, OrderType::Limit, 100, 4));
    book.addOrder(Order(5, 40, Side::Buy, OrderType::Limit, 95, 5));

    assert(book.getBestBid() == 100);
    assert(book.getBestAsk() == 105);
    assert(book.getOrderCount() == 5);

    auto trades = book.addOrder(Order(6, 120, Side::Buy, OrderType::Limit, 105, 6));
    printTrades(trades);
    assert(trades.size() == 2);
    assert(trades[0].buyOrderId == 6 && trades[0].sellOrderId == 1 && trades[0].quantity == 100 && trades[0].price == 105);
    assert(trades[1].buyOrderId == 6 && trades[1].sellOrderId == 2 && trades[1].quantity == 20 && trades[1].price == 105);
    assert(book.getBestAsk() == 105);
    assert(book.getOrderCount() == 4);

    auto marketTrades = book.addOrder(Order(7, 50, Side::Buy, OrderType::Market, 0, 7));
    printTrades(marketTrades);
    assert(marketTrades.size() == 2);
    assert(marketTrades[0].sellOrderId == 2 && marketTrades[0].quantity == 30 && marketTrades[0].price == 105);
    assert(marketTrades[1].sellOrderId == 3 && marketTrades[1].quantity == 20 && marketTrades[1].price == 110);
    assert(book.getBestAsk() == 110);
    assert(book.getOrderCount() == 3);

    assert(book.cancelOrder(4));
    assert(!book.cancelOrder(4));
    assert(book.getBestBid() == 95);
    assert(book.getOrderCount() == 2);

    auto sellTrades = book.addOrder(Order(8, 100, Side::Sell, OrderType::Limit, 90, 8));
    printTrades(sellTrades);
    assert(sellTrades.size() == 1);
    assert(sellTrades[0].buyOrderId == 5 && sellTrades[0].sellOrderId == 8 && sellTrades[0].quantity == 40 && sellTrades[0].price == 95);
    assert(!book.getBestBid().has_value());
    assert(book.getBestAsk() == 90);
    assert(book.getOrderCount() == 2);

    std::cout << "All checks passed. Active orders: " << book.getOrderCount() << '\n';
    return 0;
}