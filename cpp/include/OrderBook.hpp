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
    
}