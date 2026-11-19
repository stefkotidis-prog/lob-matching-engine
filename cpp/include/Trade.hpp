#pragma once
#include "Types.hpp"

struct Trade {
    OrderId buyOrderId;
    OrderId sellOrderId;
    Quantity quantity;
    Price price;
    Timestamp timestamp;
};