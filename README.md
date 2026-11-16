
# Limit Order Book (LOB) Matching Engine
[![Limit Order Book CI](https://github.com/stefkotidis-prog/lob-matching-engine/actions/workflows/ci.yml/badge.svg)](https://github.com/stefkotidis-prog/lob-matching-engine/actions/workflows/ci.yml)

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

The project is built using Maven. To compile and run the engine locally:

```bash
# Compile the project and run all unit tests
mvn clean test

# Run the core matching engine simulation
mvn exec:java -Dexec.mainClass="Engine"