#include "events.h"
#include <random>
#include <ctime>
#include <iostream>


// Utility function: generates a random decimal between minValue and maxValue
// Used to apply random changes to leader popularity, stance, or population.
//
// Example: randomChange(-0.10, 0.10) → could return 0.0345 or -0.0872
//
// Note: The static keyword ensures the random generator keeps its seed
// between calls — otherwise, repeated calls in quick succession
// could produce identical random numbers.

double randomChange(double minValue, double maxValue) {
    static std::default_random_engine generator(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_real_distribution<double> dis(minValue, maxValue);
    return dis(generator);
}


// Base Event Class
// Represents a general event that can affect the election simulation.
// Each subclass implements its own version of applyEvent().

Event::Event(std::string name, double probability) {
    eventName = name;              // Set the event name (e.g. "Population Change")
    eventProbability = probability; // The likelihood of this event occurring
}

// Returns the name of the event
std::string Event::getName() { 
    return eventName; 
}

// Returns the probability of the event
double Event::getProbability() { 
    return eventProbability; 
}

// Popularity Change
// This event represents a change in a leader's popularity.
// When triggered, it adjusts the leader’s popularity randomly.

PopularityChange::PopularityChange()
    : Event("Leader Popularity Change", 0.25) {} // 25% base probability

void PopularityChange::applyEvent(Leader& leader, Division&) {
    // Generate a random popularity change between -0.10 and +0.10
    double change = randomChange(-0.10, 0.10);

    // Apply the change to the leader’s popularity
    leader.adjustPopularity(change);

    // Display the outcome for debugging or simulation log
    std::cout << leader.getName()
              << "'s popularity changed by " << change << "\n";
}


// PolicyShift
// Represents a shift in how a leader changes stance on an issue.
// In this case, it applies a random shift to one of the division’s stances.

PolicyShift::PolicyShift()
    : Event("Leader changed stance on issue", 0.25) {} // 25% base probability

void PolicyShift::applyEvent(Leader& leader, Division& division) {
    // Pick a random issue index (0–4) since there are 5 national issues
    int issueIndex = rand() % 5;

    // Generate small random changes in significance and strength
    double sigChange = randomChange(-0.10, 0.10);
    double strChange = randomChange(-0.10, 0.10);

    // Shift the division’s stance on this issue
    division.shiftStance(issueIndex, sigChange, strChange);

    // Log the event for clarity in simulation output
    std::cout << "Division: " << division.getName()
              << " shifted stance on issue " << issueIndex << "\n";
}


// PublicOpinionShift
// Represents a random change in a division’s stance on one issue.
// This might simulate an event like media influence or local debate.


PublicOpinionShift::PublicOpinionShift()
    : Event("Division Stance Change", 0.25) {}

void PublicOpinionShift::applyEvent(Leader&, Division& division) {
    // Pick a random issue index (0–4)
    int issueIndex = rand() % 5;

    // Generate small random changes in significance and strength
    double sigChange = randomChange(-0.10, 0.10);
    double strChange = randomChange(-0.10, 0.10);

    // Apply the changes to the division’s stance
    division.shiftStance(issueIndex, sigChange, strChange);

    // Output the change to the console
    std::cout << "Division: " << division.getName()
              << " shifted stance on issue " << issueIndex << "\n";
}


// Population Change Event
// Simulates a change in a division’s population (e.g. migration, growth).
// Randomly increases or decreases population by up to 10%.

PopulationChange::PopulationChange() : Event("Population Change", 0.25) {}

void PopulationChange::applyEvent(Leader&, Division& division) {
    // Generate a small random population change between -10% and +10%
    double change = randomChange(-0.10, 0.10);

    // Apply the change to the division’s population (bounded in [0.5, 1.5])
    division.changePopulation(change);

    // Print a readable event message
    std::cout << "Division: " << division.getName()
        << " population changed by " << change << "\n";
}
