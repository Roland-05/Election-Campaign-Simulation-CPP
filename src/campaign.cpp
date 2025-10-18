
// campaign.cpp
// Description:
// Implements the Campaign controller that coordinates parties, divisions,
// and daily campaign events in Wonderland. This class controls:
//  - Initialisation (setup) of parties and divisions
//  - Simulation of daily probabilistic events
//  - Election day scoring and result output


#include "campaign.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>   // for formatting numbers
#include <random>    // for stance randomization

// Utility: generate random double between [min, max]
static double randomDouble(double minValue, double maxValue) {
    static std::default_random_engine generator(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_real_distribution<double> dis(minValue, maxValue);
    return dis(generator);
}

// Constructor: create event objects and initialise campaign parameters
Campaign::Campaign(int divisions, int days)
    : numDivisions(divisions), numDays(days) {
    
    events[0] = new PopularityChange();
    events[1] = new PolicyShift();
    events[2] = new PublicOpinionShift();
    events[3] = new PopulationChange();
}

// Destructor: clean up allocated event objects
Campaign::~Campaign() {
    for (int i = 0; i < NUM_EVENTS; i++)
        delete events[i];
}


// Setup phase: create parties, leaders, and divisions, then randomise stances
void Campaign::setup() {

    // Create leaders with random base popularity values 
    // instead of hardcoding (0.6, 0.5, 0.4), we randomise within [0.3, 0.9].
    // this ensures each simulation is slightly different, matching assignment requirements.
    Leader l1("Alice", randomDouble(0.3, 0.9));
    Leader l2("Bob",   randomDouble(0.3, 0.9));
    Leader l3("Edmund", randomDouble(0.3, 0.9));

    // assign leaders to parties
    parties[0] = Party("Liberal Party", l1);
    parties[1] = Party("Greens", l2);
    parties[2] = Party("Capitalists", l3);

    // create divisions with random population 
    // each division gets a unique name and a random population between 0.5 and 1.5
    for (int i = 0; i < numDivisions; i++) {
        std::string name = "Division_" + std::to_string(i + 1);
        double population = randomDouble(0.5, 1.5);  // uniform [0.5, 1.5]
        divisions[i] = Division(name, population);
    }

    // randomise stances for leaders and divisions
    for (int p = 0; p < NUM_PARTIES; ++p) {
        // create 5 stances for each party
        for (int i = 0; i < 5; ++i) {
        // each stance is a pair (significance,strength), both from (0.01, 1.0]
            double sig = randomDouble(0.01, 1.0);
            double str = randomDouble(0.01, 1.0);
            parties[p].getLeader().setStance(i, Stance(sig, str));
        }
    }

    // randomise stances for every division
    // represents how important each issue is to that division
    for (int d = 0; d < numDivisions; ++d) {
        for (int i = 0; i < 5; ++i) {
            double sig = randomDouble(0.01, 1.0);
            double str = randomDouble(0.01, 1.0);
            divisions[d].setStance(i, Stance(sig, str));
        }
    }

    // --- Output setup summary ---
    std::cout << "[Setup] Created 3 parties and "
              << numDivisions << " divisions.\n";

    // show the show the list of divisions with their populations
    std::cout << "\nInitial Nation Report\n";
    for (int d = 0; d < numDivisions; ++d) {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << divisions[d].getName()
                  << " | Population: " << divisions[d].getPopulation() << "M\n";
    }

    // show the list of parties and their leaders' popularity
    std::cout << "\nParty Report\n";
    for (int p = 0; p < NUM_PARTIES; ++p) {
        std::cout << parties[p].getName() << " led by "
                  << parties[p].getLeader().getName()
                  << " | Popularity: " << parties[p].getLeader().getPopularity() << "\n";
    }
}


// Run phase: simulate each event day of the campaign
// ---------------------------------------------------------------------------
void Campaign::run() {
    // reseed the standard random generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::cout << "\n--- Simulation of daily events ---\n";

    // repeat for each campaign day
    for (int day = 1; day <= numDays; day++) {
        std::cout << "\nEvent Day " << day << "\n";

        // Each division experiences a random event, applied to a random party leader
        for (int d = 0; d < numDivisions; d++) {

            int eIndex = std::rand() % NUM_EVENTS;    // random event (0–3)
            int pIndex = std::rand() % NUM_PARTIES;   // random leader (0–2)

            // The applyEvent() method will modify leader/division attributes
            // Where random campaign happenings change the world state
            events[eIndex]->applyEvent(
                parties[pIndex].getLeader(),
                divisions[d]
            );
        }
    }
}


// Results phase: compute election results based on final stances & popularity
void Campaign::results() {
    std::cout << "\nElection Results\n";

    int wins[NUM_PARTIES] = {0};

    // For each division, compute which party’s leader wins
    for (int d = 0; d < numDivisions; d++) {
        double bestScore = -1.0; // highest score so far
        int bestParty = -1; // index of winning party for this division

        // calculate each party's score in this division
        for (int p = 0; p < NUM_PARTIES; p++) {
            double stanceSum = 0.0;


            // Compute average cosine similarity over 5 issues
            for (int i = 0; i < 5; i++) {
                stanceSum += Stance::cosine(
                    divisions[d].getStance(i),
                    parties[p].getLeader().getStance(i)
                );
            }
            // The average of the 5 cosine similarities gives a
            // single alignment score for this leader–division pair.
            double avgCos = stanceSum / 5.0; // mean stance similarity

            // weighted by population
            double popFactor = avgCos * divisions[d].getPopulation();

            // The total score formula uses weights A and B:
            // score = 0.7 * (stance-population factor) + 0.3 * popularity
            // A is greater than B, meaning stance alignment matters more than raw popularity.
            // Voting score formula: A * (stance-population factor) + B * popularity
            const double A = 0.7, B = 0.3;
            double score = A * popFactor + B * parties[p].getLeader().getPopularity();
            
            // keep track of the best-scoring party for this division
            if (score > bestScore) {
                bestScore = score;
                bestParty = p;
            }
        }

        // Track which party won the division
        wins[bestParty]++;
        // print division-level result
        std::cout << divisions[d].getName() << " won by "
                  << parties[bestParty].getName()
                  << " (score = " << std::fixed << std::setprecision(3)
                  << bestScore << ")\n";
    }

    // National Summary 
    std::cout << "\nNational Summary\n";
    int maxWins = 0; // track max divisions won by any party

    // display division win counts
    for (int p = 0; p < NUM_PARTIES; p++) {
        std::cout << parties[p].getName() << " won "
                  << wins[p] << " divisions.\n";
        if (wins[p] > maxWins) maxWins = wins[p];
    }

    // Determine if hung parliament or clear winner
    int winners = 0;
    int winnerIndex = -1;
    for (int p = 0; p < NUM_PARTIES; p++) {
        if (wins[p] == maxWins) {
            winners++; // count how many have same top score
            winnerIndex = p; // remember the last one that achieved it
        }
    }
    // final outcome message
    if (winners == 1)
        std::cout << "\nWinner: " << parties[winnerIndex].getName()
                  << " led by " << parties[winnerIndex].getLeader().getName() << "\n";
    else
        std::cout << "\nHung parliament!\n";
}
