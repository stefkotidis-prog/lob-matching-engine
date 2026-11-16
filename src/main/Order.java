package main;
public record Order(
    String id, 
    boolean isBuy, 
    double price, 
    int quantity, 
    long sequenceId
) {
    /**
     * Returns a new Order instance with updated quantity to maintain immutability.
     */
    public Order withQuantity(int newQuantity) {
        return new Order(this.id, this.isBuy, this.price, newQuantity, this.sequenceId);
    }
}