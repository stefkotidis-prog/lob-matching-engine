#pragma once
#include <stdexcept>
#include "Types.hpp"

class Order {
    private:
        OrderId id_;
        Quantity initialQuantity_;
        Quantity remainingQuantity_;
        Price price_;
        Timestamp timestamp_;
        Side side_;
        OrderType type_;

    public: 
        Order(OrderId id,Quantity quantity, Side side,OrderType type, Price price, Timestamp timestamp): 
            id_(id),
            initialQuantity_(quantity),
            remainingQuantity_(quantity),
            price_(price),
            timestamp_(timestamp),
            side_(side),
            type_(type)
        {
            if(quantity == 0){
                throw std::invalid_argument("Quantity must be greater than zero");
            }
        }
        

    OrderId getId() const{return id_;}
    Price getPrice() const{return price_;}
    Timestamp getTimestamp() const{ return timestamp_;}
    Quantity getInitialQuantity() const {return initialQuantity_;}
    Quantity getRemainingQuantity() const {return remainingQuantity_;}
    Side getSide() const {return side_;}
    OrderType getOrderType() const {return type_;}
    bool isFilled() const { return remainingQuantity_== 0;}

    void fill(Quantity quantity){
        if (quantity == 0 || quantity > remainingQuantity_){
            throw std::invalid_argument("Invalid order amount");
        }
        remainingQuantity_ -= quantity;
    }

    
};
