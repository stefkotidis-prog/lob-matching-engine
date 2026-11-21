#pragma once
#include <cstddef>          
#include <functional>       
#include <list>            
#include <map>           
#include <optional>        
#include <unordered_map>   
#include <vector>           
#include "Trade.hpp"
#include "Order.hpp"

class OrderBook {
private:

    using OrderQueue = std::list<Order>;

    struct OrderLocation{
        Price price;
        OrderQueue::iterator position;
        Side side;
    };

    std::map<Price, OrderQueue, std::greater<Price>> buy_;

    std::map<Price, OrderQueue> sell_;

    std::unordered_map<OrderId, OrderLocation> orderIndex_;

    void matchOrder(Order& order, std::vector<Trade>& trades);

public: 

    OrderBook() = default;
    OrderBook(const OrderBook&) = delete;
    OrderBook& operator=(const OrderBook&) = delete;
    
    std::vector<Trade> addOrder(Order order);

    bool cancelOrder(OrderId orderId);

    std::optional<Price> getBestBid() const;
    std::optional<Price> getBestAsk() const;
    std::size_t getOrderCount() const;
};