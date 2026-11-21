# Limit Order Book (LOB) Matching Engine

[![Limit Order Book CI](https://github.com/stefkotidis-prog/lob-matching-engine/actions/workflows/ci.yml/badge.svg?branch=main)](https://github.com/stefkotidis-prog/lob-matching-engine/actions/workflows/ci.yml)

A deterministic Limit Order Book (LOB) matching engine implementing strict **Price-Time Priority**, with parallel implementations in **C++20** and **Java**.

## Project Structure

```text
.
├── cpp/        # C++20 implementation (CMake, Limit & Market orders, O(log P) price levels)
├── java/       # Java implementation (Maven, Priority Queue based matching)
└── .github/    # GitHub Actions CI workflows
```

## Architecture

### C++20 (`cpp/`)

Built around price-level queues indexed by order ID for deterministic matching and fast cancellation:

- **Bids (`buy_`):** `std::map<Price, std::list<Order>, std::greater<Price>>` ordered from highest to lowest price, with FIFO queues at each price level.
- **Asks (`sell_`):** `std::map<Price, std::list<Order>>` ordered from lowest to highest price, with FIFO queues at each price level.
- **Order Index (`orderIndex_`):** `std::unordered_map<OrderId, OrderLocation>` storing each resting order's side, price level, and list iterator for direct cancellation.
- **Order Types:** Supports both `Limit` and `Market` orders using fixed-width integer types (`int64_t` / `uint64_t`) to avoid floating-point precision issues.

| **Operation**             | **Time Complexity** |
| -------------------------- | ------------------- |
| Insert Limit Order         | `O(log P)`          |
| Cancel Order               | `O(log P)`          |
| Best Bid / Ask             | `O(1)`              |
| Match (per resting order)  | `O(1)` amortized     |

*Where `P` is the number of active price levels.*

### Java (`java/`)

Built upon two binary heaps:

- **Bids (Buy Orders):** Max-Heap sorted by highest price, breaking ties by lowest `sequenceId` (FIFO).
- **Asks (Sell Orders):** Min-Heap sorted by lowest price, breaking ties by lowest `sequenceId` (FIFO).

| **Operation**             | **Time Complexity** |
| -------------------------- | ------------------- |
| Order Insertion            | `O(log N)`          |
| Best Price Retrieval       | `O(1)`              |
| Order Execution / Removal  | `O(log N)`          |

*Where `N` is the number of resting orders.*

## Quick Start

### C++20

Requires CMake 3.16+ and a C++20-compatible compiler.

```bash
cd cpp
cmake -S . -B build
cmake --build build
./build/lob_engine
```

### Java

Requires JDK and Maven.

```bash
cd java
mvn clean test
mvn exec:java -Dexec.mainClass="Engine"
```