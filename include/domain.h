#ifndef MYCLASS_H
#define MYCLASS_H
#include <string>

//  STANCE CLASS 
// Represents a position on an issue.
// Has significance (importance) and measureStrength (how strong the stance is).
class Stance {
private:
    double significance;    // How important the issue is (0.01 to 1.0)
    double measureStrength;   // How strongly the stance is held (0.01 to 1.0)

    // Keeps values in range (0.01, 1.0)
    double keepValueInRange(double value);

public:
    Stance(); // Default constructor
    Stance(double significance, double measurestrength); // Custom constructor

    double getSignificance();   // Returns significance
    double getMeasureStrength();  // Returns measure strength

    void shift(double changeInSignificance, double changeInStrength);

    static double cosine(Stance stanceA, Stance stanceB); // Static similarity function
};

// ISSUE CLASS 
// Stores an issue’s name and description.
class Issue {
private:
    std::string issueName;         // The name of the issue (e.g., "Healthcare")
    std::string issueDescription;  // Short blurb or explanation

public:
    Issue();                                        // Default constructor
    Issue(std::string name, std::string description); // Constructor with parameters

    std::string getName();         // Returns the issue name
    std::string getDescription();  // Returns the issue description
};

// Leader class
// Represents a political leader with 5 stances and a popularity value.
class Leader {
private:
    std::string leaderName; // Leader’s name
    double leaderPopularity;  // Popularity (0.01 to 1.0)
    Stance leaderStances[5];      // Array of 5 issue stances

    // Keeps popularity value in valid range [0.01, 1.0]
    double keepValueInRange(double value);

public:
    Leader();                                        // Default constructor
    Leader(std::string name, double popularity);     // Custom constructor

    std::string getName();  // Returns leader’s name
    double getPopularity(); // Returns popularity

    void setStance(int issueIndex, Stance stance);   // Sets stance for a given issue
    Stance getStance(int issueIndex);                // Gets stance for a given issue

    void adjustPopularity(double popularityChange);  // Adjusts popularity
    void shiftStance(int issueIndex,
                     double changeInSignificance,
                     double changeInStrength);       // Shifts stance for a given issue
};

// PARTY CLASS 
// Represents a political party and its leader.
class Party {
private:
    std::string partyName;   // Party name
    Leader partyLeader; // Leader object

public:
    Party(); // Default constructor
    Party(std::string name, Leader leader);         // Custom constructor

    std::string getName();  // Returns party name
    Leader& getLeader();  // Returns reference to leader
};

// DIVISION CLASS
// Represents a voting region with population and 5 issue stances.
class Division {
private:
    std::string divisionName;  // Division name
    Stance divisionStances[5];  // Array of 5 issue stances
    double divisionPopulation; // Population factor [0.5, 1.5]

    // Keeps population value in valid range [0.5, 1.5]
    double keepValueInRange(double value);

public:
    Division();                                     // Default constructor
    Division(std::string name, double population);  // Custom constructor

    std::string getName();      // Returns division name
    double getPopulation();     // Returns population

    void setStance(int issueIndex, Stance stance);  // Sets stance for a given issue
    Stance getStance(int issueIndex);               // Gets stance for a given issue

    void shiftStance(int issueIndex,
                     double changeInSignificance,
                     double changeInStrength);      // Shifts stance values
    void changePopulation(double populationChange); // Adjusts population
};

#endif 
