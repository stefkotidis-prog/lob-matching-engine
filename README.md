
# Limit Order Book (LOB) Matching Engine

(Α C++ implementation of this project is planned for the near future.)

A deterministic Limit Order Book (LOB) matching engine implementing strictly enforced **Price-Time Priority**.

## Architecture

The core matching engine is built upon two Priority Queues :

- **Bids (Buy Orders):** Implemented as a **Max-Heap**. Orders are sorted by highest price. Ties are broken by the lowest `sequenceId` (FIFO).
- **Asks (Sell Orders):** Implemented as a **Min-Heap**. Orders are sorted by lowest price. Ties are broken by the lowest `sequenceId`.

### Time Complexity

| Operation | Time Complexity |
|---|---|
| Order Insertion | `O(log n)` |
| Best Price Retrieval (Peek) | `O(1)` |
| Order Execution / Removal | `O(log n)` |

## Quick Start

To compile and run the simulation engine:

```bash
# Compile the Java source files
javac Engine.java OrderBook.java Order.java Trade.java

# Run the simulation
java Engine
```