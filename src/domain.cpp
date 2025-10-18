#include <string>
#include <cmath>
#include "domain.h"


//STANCE CLASS
// Represents a stance or opinion on an issue.
// Contains significance (importance of the issue)
// and measureStrength (how strongly the stance is held).
//

// Helper method: keeps a value in range [0.01, 1.0]
double Stance::keepValueInRange(double value) {
    if (value < 0.01) { value = 0.01; }
    if (value > 1.0) { value = 1.0; }
    return value;
}

// Default constructor
Stance::Stance() {
    significance = 0.5;
    measureStrength = 0.5;
}

// Custom constructor
Stance::Stance(double sig, double strength) {
    significance = keepValueInRange(sig);
    measureStrength = keepValueInRange(strength);
}

// Getter for significance
double Stance::getSignificance() {
    return significance;
}

// Getter for measureStrength
double Stance::getMeasureStrength() {
    return measureStrength;
}

// Adjusts stance values, keeping them within valid range
void Stance::shift(double changeInSignificance, double changeInStrength) {
    significance = keepValueInRange(significance + changeInSignificance);
    measureStrength = keepValueInRange(measureStrength + changeInStrength);
}

// Static method to compute similarity between two stances using cosine similarity
double Stance::cosine(Stance stanceA, Stance stanceB) {
    // compute dot product of hte two stances.
    // this measure how much they point in the same direction
    double dotProduct = (stanceA.significance * stanceB.significance) +
                        (stanceA.measureStrength * stanceB.measureStrength);

    // compute magnitudes (lengths) of each stance
    double magnitudeA = std::sqrt((stanceA.significance * stanceA.significance) +
                                  (stanceA.measureStrength * stanceA.measureStrength));
    
    double magnitudeB = std::sqrt((stanceB.significance * stanceB.significance) +
                                  (stanceB.measureStrength * stanceB.measureStrength));
    // if either has zero magnitude, similarity cannot be computed
    // to prevent division by zero, we return 0 to indicate no similarity 
    if (magnitudeA == 0 || magnitudeB == 0)
        return 0.0;
    // return normalised cosine similarity
    return dotProduct / (magnitudeA * magnitudeB);
}

//
// ---------------- ISSUE CLASS ----------------
// Represents a national issue with a name and short description.
//

// Default constructor
Issue::Issue() {
    issueName = "Default";
    issueDescription = "No description provided.";
}

// Constructor with parameters
Issue::Issue(std::string name, std::string description) {
    issueName = name;
    issueDescription = description;
}

// Returns the issue name
std::string Issue::getName() {
    return issueName;
}

// Returns the issue description
std::string Issue::getDescription() {
    return issueDescription;
}

//
// ---------------- LEADER CLASS ----------------
// Represents a political leader with 5 stances and a popularity rating.
//

// Keeps popularity within [0.01, 1.0]
double Leader::keepValueInRange(double value) {
    if (value > 1.0) { value = 1.0; }
    if (value < 0.01) { value = 0.01; }
    return value;
}

// Default constructor
Leader::Leader() {
    leaderName = "Unknown";
    leaderPopularity = 0.5;
}

// Custom constructor
Leader::Leader(std::string name, double popularity) {
    leaderName = name;
    leaderPopularity = keepValueInRange(popularity);
}

// Returns leader name
std::string Leader::getName() {
    return leaderName;
}

// Returns leader popularity
double Leader::getPopularity() {
    return leaderPopularity;
}

// Sets stance for a particular issue index (0–4)
void Leader::setStance(int issueIndex, Stance stance) {
    if (issueIndex >= 0 && issueIndex < 5) {
        leaderStances[issueIndex] = stance;
    }
}

// Returns stance for a particular issue index (0–4)
Stance Leader::getStance(int issueIndex) {
    if (issueIndex >= 0 && issueIndex < 5) {
        return leaderStances[issueIndex];
    }
    // Return default if invalid index
    return Stance();
}

// Adjusts popularity within range
void Leader::adjustPopularity(double popularityChange) {
    leaderPopularity = keepValueInRange(leaderPopularity + popularityChange);
}

// Shifts stance for a particular issue
void Leader::shiftStance(int issueIndex, double changeInSignificance, double changeInStrength) {
    if (issueIndex >= 0 && issueIndex < 5) {
        leaderStances[issueIndex].shift(changeInSignificance, changeInStrength);
    }
}

//
// ---------------- PARTY CLASS ----------------
// Represents a political party with a name and a leader.
//

// Default constructor
Party::Party() {
    partyName = "";
}

// Custom constructor
Party::Party(std::string name, Leader leader) {
    partyName = name;
    partyLeader = leader;
}

// Returns party name
std::string Party::getName() {
    return partyName;
}

// Returns reference to the leader
Leader& Party::getLeader() {
    return partyLeader;
}

//
// ---------------- DIVISION CLASS ----------------
// Represents a voting region with 5 stances and population factor.
//

// Keeps population within [0.5, 1.5]
double Division::keepValueInRange(double value) {
    if (value < 0.5) { value = 0.5; }
    if (value > 1.5) { value = 1.5; }
    return value;
}

// Default constructor
Division::Division() {
    divisionName = "";
    divisionPopulation = 1.0;
}

// Custom constructor
Division::Division(std::string name, double population) {
    divisionName = name;
    divisionPopulation = keepValueInRange(population);
}

// Returns division name
std::string Division::getName() {
    return divisionName;
}

// Returns population factor
double Division::getPopulation() {
    return divisionPopulation;
}

// Sets stance for a particular issue index
void Division::setStance(int issueIndex, Stance stance) {
    if (issueIndex >= 0 && issueIndex < 5) {
        divisionStances[issueIndex] = stance;
    }
}

// Returns stance for a particular issue
Stance Division::getStance(int issueIndex) {
    if (issueIndex >= 0 && issueIndex < 5) {
        return divisionStances[issueIndex];
    }
    return Stance();
}

// Shifts stance values for one issue
void Division::shiftStance(int issueIndex, double changeInSignificance, double changeInStrength) {
    if (issueIndex >= 0 && issueIndex < 5) {
        divisionStances[issueIndex].shift(changeInSignificance, changeInStrength);
    }
}

// Changes population while keeping it in range
void Division::changePopulation(double populationChange) {
    divisionPopulation = keepValueInRange(divisionPopulation + populationChange);
}
