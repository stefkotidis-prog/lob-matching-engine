package main.java;
import java.util.concurrent.atomic.AtomicLong;

public class Engine {

    private static final AtomicLong sequenceGenerator = new AtomicLong(0);

    public static void main(String[] args) {
        OrderBook book = new OrderBook();

        System.out.println("Initializing Limit Order Book Simulation...\n");

        // 1. Add some initial liquidity (Resting Orders)
        book.processOrder(createOrder("SELL-1", false, 102.50, 100));
        book.processOrder(createOrder("SELL-2", false, 102.00, 50)); // Better price, will be front of Asks
        book.processOrder(createOrder("BUY-1", true, 99.00, 200));
        book.processOrder(createOrder("BUY-2", true, 99.50, 150));   // Better price, will be front of Bids

        book.printBookState();

        // 2. Incoming Marketable Order (Crosses the spread)
        System.out.println("Incoming Aggressive Buy Order...");
        // Wants to buy 70 shares at 102.50 max. 
        // Should consume the 50 shares at 102.00, and 20 shares from the 102.50 ask.
        book.processOrder(createOrder("BUY-3", true, 102.50, 70));

        book.printBookState();
    }

    /**
     * Helper factory method to automatically increment the sequenceId.
     */
    private static Order createOrder(String id, boolean isBuy, double price, int quantity) {
        return new Order(id, isBuy, price, quantity, sequenceGenerator.incrementAndGet());
    }
}