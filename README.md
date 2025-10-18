# Election Campaign Simulation — C++

A C++ object-oriented simulation that models a national election campaign across multiple divisions.  
Developed to demonstrate advanced **OOP design**, **inheritance**, **composition**, **polymorphism**, and **data-driven simulation**.

---

## Overview
The program simulates political parties, leaders, electoral divisions, and daily campaign events.  
Each simulation produces unique outcomes based on randomised attributes and probabilistic event effects.

---

## Core Components
- **Stance** – Represents opinions on five national issues using two continuous attributes: significance and measure strength.  
- **Leader / Party** – Each leader has five issue stances and a bounded popularity score.  
- **Division** – Represents an electoral region with population and stance profile.  
- **Event** (abstract) – Base class for daily campaign events; subclasses include:
  - `PopularityChange`
  - `PolicyShift`
  - `PublicOpinionShift`
  - `PopulationChange`
- **Campaign** – Coordinates simulation setup, event days, and election results.

---

## Key Concepts Demonstrated
| Concept | Example |
|----------|----------|
| **Encapsulation** | Private attributes with accessor methods |
| **Inheritance & Polymorphism** | `Event` subclasses override `applyEvent()` |
| **Composition** | `Party` owns a `Leader`, `Leader` owns `Stance` objects |
| **Aggregation** | `Campaign` aggregates `Division` and `Party` objects |
| **Randomness** | Time-seeded random number generation ensures unique runs |
| **Cosine Similarity** | Measures stance alignment between leaders and divisions |

---

## Mathematical Model

Each simulation uses randomised continuous values and weighted formulas to model real-world political dynamics.
x ∈ (0.01, 1.0)

This range ensures natural diversity while avoiding extremes.

### 2. Cosine Similarity
The alignment between a leader’s and a division’s stance on each issue is calculated as:

cosine(X, Y) = (X₁×Y₁ + X₂×Y₂) / (√(X₁²+X₂²) × √(Y₁²+Y₂²))


This yields a value between **0 (opposed)** and **1 (aligned)**.

### 3. Scoring Formula
A division’s support for a leader is computed using a weighted formula:

Score = 0.7 × (Stance–Population Factor) + 0.3 × (Popularity)

Where:
- **Stance–Population Factor** = average cosine similarity × division population  
- **Popularity** adjusts daily via random events bounded in (0.01, 1.0)

The leader with the highest score in each division wins that division.  
The party with the most division wins forms the government.

### 4. Randomness
Randomisation is time-seeded (`srand(time(nullptr))`) so every simulation produces unique outcomes, ensuring stochastic behaviour across runs.

---

## Build Instructions
Clone the repository and compile using `g++` (C++17 or later):

```bash
git clone https://github.com/<yourusername>/election-campaign-simulation-cpp.git
cd election-campaign-simulation-cpp

g++ campaign.cpp events.cpp domain.cpp main.cpp -std=c++17 -o program
./program <num_divisions> <num_days>


---

## Build Instructions
Clone the repository and compile using `g++` (C++17 or later):
```bash
git clone https://github.com/<yourusername>/election-campaign-simulation-cpp.git
cd election-campaign-simulation-cpp

g++ campaign.cpp events.cpp domain.cpp main.cpp -std=c++17 -o program
./program <num_divisions> <num_days>

---

## Sample Output
Election Results
Division 1 won by Capitalists (score = 0.671)
Division 2 won by Capitalists (score = 0.690)
Division 3 won by Capitalists (score = 0.713)
Division 4 won by Capitalists (score = 0.824)
Division 5 won by Greens (score = 1.136)

Liberal Party won 0 divisions.
Greens won 1 divisions.
Capitalists won 4 divisions.
Winner: Capitalists led by Edmund

---

## File Structure
election-campaign-simulation-cpp/
├── campaign.cpp
├── domain.cpp
├── events.cpp
├── main.cpp
├── README.md
└── (header files as needed)

---

## Concepts Learned
- Applying OOP principles in large-scale simulations  
- Managing inter-class relationships and object lifecycles  
- Implementing randomised events and probability models  
- Structuring modular multi-file C++ applications


