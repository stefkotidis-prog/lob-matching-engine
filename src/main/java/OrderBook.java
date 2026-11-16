package main.java;
import java.util.Comparator;
import java.util.PriorityQueue;

public class OrderBook {

    // Max-Heap: Highest price first. If prices are equal, lowest sequenceId (oldest) first.
    private final PriorityQueue<Order> bids;
    
    // Min-Heap: Lowest price first. If prices are equal, lowest sequenceId (oldest) first.
    private final PriorityQueue<Order> asks;

    public OrderBook() {
        Comparator<Order> bidComparator = Comparator
            .comparingDouble(Order::price)
            .reversed()
            .thenComparingLong(Order::sequenceId);

        Comparator<Order> askComparator = Comparator
            .comparingDouble(Order::price)
            .thenComparingLong(Order::sequenceId);

        this.bids = new PriorityQueue<>(bidComparator);
        this.asks = new PriorityQueue<>(askComparator);
    }

    /**
     * Entry point for a new incoming order. Routes to appropriate matching logic.
     */
    public void processOrder(Order incomingOrder) {
        if (incomingOrder.isBuy()) {
            incomingOrder = matchIncomingBuy(incomingOrder);
            if (incomingOrder.quantity() > 0) {
                bids.add(incomingOrder);
            }
        } else {
            incomingOrder = matchIncomingSell(incomingOrder);
            if (incomingOrder.quantity() > 0) {
                asks.add(incomingOrder);
            }
        }
    }

    private Order matchIncomingBuy(Order buyOrder) {
        while (buyOrder.quantity() > 0 && !asks.isEmpty() && buyOrder.price() >= asks.peek().price()) {
            Order bestAsk = asks.poll();
            int tradedQuantity = Math.min(buyOrder.quantity(), bestAsk.quantity());

            Trade trade = new Trade(buyOrder.id(), bestAsk.id(), bestAsk.price(), tradedQuantity);
            System.out.println(trade);

            buyOrder = buyOrder.withQuantity(buyOrder.quantity() - tradedQuantity);
            int remainingAskQuantity = bestAsk.quantity() - tradedQuantity;

            if (remainingAskQuantity > 0) {
                asks.add(bestAsk.withQuantity(remainingAskQuantity));
            }
        }
        return buyOrder;
    }

    private Order matchIncomingSell(Order sellOrder) {
        while (sellOrder.quantity() > 0 && !bids.isEmpty() && sellOrder.price() <= bids.peek().price()) {
            Order bestBid = bids.poll();
            int tradedQuantity = Math.min(sellOrder.quantity(), bestBid.quantity());

            Trade trade = new Trade(bestBid.id(), sellOrder.id(), bestBid.price(), tradedQuantity);
            System.out.println(trade);

            sellOrder = sellOrder.withQuantity(sellOrder.quantity() - tradedQuantity);
            int remainingBidQuantity = bestBid.quantity() - tradedQuantity;

            if (remainingBidQuantity > 0) {
                bids.add(bestBid.withQuantity(remainingBidQuantity));
            }
        }
        return sellOrder;
    }
    
    public void printBookState() {
        System.out.println("\n--- Order Book State ---");
        System.out.println("Bids (Buyers) waiting: " + bids.size());
        System.out.println("Asks (Sellers) waiting: " + asks.size());
        System.out.println("------------------------\n");
    }
}