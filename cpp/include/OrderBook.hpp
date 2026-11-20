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

std::unordered_map<OrderId, OrderLocation> tradeIndex_;

void assignTrade(Order& order, std::vector<Trade>& trade);
//follow up from here
};