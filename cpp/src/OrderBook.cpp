#include "OrderBook.hpp"
std::optional<Price> OrderBook::getBestBid() const{
    if (buy_.empty()){
        return std::nullopt;
    }
    return buy_.begin()->first;
}

std::optional<Price> OrderBook::getBestAsk() const{
    if (sell_.empty()){
        return std::nullopt;
    }
    return sell_.begin()->first;
}

std:: size_t OrderBook::getOrderCount() const {
    return orderIndex_.size();
}