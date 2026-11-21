#include "OrderBook.hpp"
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <utility>

std::vector<Trade> OrderBook::addOrder(Order order) {
    if (orderIndex_.contains(order.getId())) {
        throw std::invalid_argument("Duplicate order id");
    }

    std::vector<Trade> trades;
    matchOrder(order, trades);

    if (!order.isFilled() && order.getOrderType() == OrderType::Limit) {
        OrderId id = order.getId();
        Price price = order.getPrice();
        Side side = order.getSide();

        if (side == Side::Buy) {
            auto& queue = buy_[price];
            queue.push_back(std::move(order));
            orderIndex_.emplace(id, OrderLocation{price, std::prev(queue.end()), side});
        } else {
            auto& queue = sell_[price];
            queue.push_back(std::move(order));
            orderIndex_.emplace(id, OrderLocation{price, std::prev(queue.end()), side});
        }
    }

    return trades;
}

bool OrderBook::cancelOrder(OrderId orderId) {
    auto indexIt = orderIndex_.find(orderId);
    if (indexIt == orderIndex_.end()) {
        return false;
    }

    const auto& location = indexIt->second;
    if (location.side == Side::Buy) {
        auto levelIt = buy_.find(location.price);
        if (levelIt != buy_.end()) {
            levelIt->second.erase(location.position);
            if (levelIt->second.empty()) {
                buy_.erase(levelIt);
            }
        }
    } else {
        auto levelIt = sell_.find(location.price);
        if (levelIt != sell_.end()) {
            levelIt->second.erase(location.position);
            if (levelIt->second.empty()) {
                sell_.erase(levelIt);
            }
        }
    }

    orderIndex_.erase(indexIt);
    return true;
}

void OrderBook::matchOrder(Order& order, std::vector<Trade>& trades) {
    if (order.getSide() == Side::Buy) {
        while (!order.isFilled() && !sell_.empty()) {
            auto bestAskIt = sell_.begin();
            Price askPrice = bestAskIt->first;

            if (order.getOrderType() == OrderType::Limit && order.getPrice() < askPrice) {
                break;
            }

            auto& queue = bestAskIt->second;
            while (!order.isFilled() && !queue.empty()) {
                Order& resting = queue.front();
                Quantity tradedQty = std::min(order.getRemainingQuantity(), resting.getRemainingQuantity());

                order.fill(tradedQty);
                resting.fill(tradedQty);

                trades.push_back(Trade{
                    order.getId(),
                    resting.getId(),
                    tradedQty,
                    askPrice,
                    order.getTimestamp()
                });

                if (resting.isFilled()) {
                    orderIndex_.erase(resting.getId());
                    queue.pop_front();
                }
            }

            if (queue.empty()) {
                sell_.erase(bestAskIt);
            }
        }
    } else {
        while (!order.isFilled() && !buy_.empty()) {
            auto bestBidIt = buy_.begin();
            Price bidPrice = bestBidIt->first;

            if (order.getOrderType() == OrderType::Limit && order.getPrice() > bidPrice) {
                break;
            }

            auto& queue = bestBidIt->second;
            while (!order.isFilled() && !queue.empty()) {
                Order& resting = queue.front();
                Quantity tradedQty = std::min(order.getRemainingQuantity(), resting.getRemainingQuantity());

                order.fill(tradedQty);
                resting.fill(tradedQty);

                trades.push_back(Trade{
                    resting.getId(),
                    order.getId(),
                    tradedQty,
                    bidPrice,
                    order.getTimestamp()
                });

                if (resting.isFilled()) {
                    orderIndex_.erase(resting.getId());
                    queue.pop_front();
                }
            }

            if (queue.empty()) {
                buy_.erase(bestBidIt);
            }
        }
    }
}

std::optional<Price> OrderBook::getBestBid() const {
    if (buy_.empty()) {
        return std::nullopt;
    }
    return buy_.begin()->first;
}

std::optional<Price> OrderBook::getBestAsk() const {
    if (sell_.empty()) {
        return std::nullopt;
    }
    return sell_.begin()->first;
}

std::size_t OrderBook::getOrderCount() const {
    return orderIndex_.size();
}