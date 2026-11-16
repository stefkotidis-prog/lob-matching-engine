package main;
public record Trade(
    String buyerId, 
    String sellerId, 
    double executionPrice, 
    int executedQuantity
) {
    @Override
    public String toString() {
        return String.format("[TRADE EXECUTED] Buyer: %s | Seller: %s | Price: %.2f | Qty: %d",
                buyerId, sellerId, executionPrice, executedQuantity);
    }
}