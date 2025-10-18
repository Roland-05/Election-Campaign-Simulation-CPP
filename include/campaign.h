// campaign.h
// Defines the Campaign class, which orchestrates the entire simulation.

// Initialise parties, leaders, and electoral divisions
// Randomise their stances and initial popularity
// Execute a series of daily events that modify attributes
// Compute final election scores and determine the winning party

#ifndef CAMPAIGN_H
#define CAMPAIGN_H

#include "domain.h"
#include "events.h"
#include <iostream>

// Campaign
// This class manages the setup, event simulation, and result computation.
// It acts as the “controller” for the Wonderland election system.

class Campaign {
private:
    int numDivisions;  // number of divisions in the simulation (1–10)
    int numDays; // number of event days before election (1–30)

    static const int NUM_PARTIES = 3;   // fixed number of parties (per spec)
    static const int NUM_EVENTS = 4;    // number of event types implemented

    Party parties[NUM_PARTIES]; // array of political parties
    Division divisions[10]; // up to 10 divisions as per spec
    Event* events[NUM_EVENTS];// array of pointers to event objects

public:
    // Constructor: initialises campaign with given divisions and event days
    Campaign(int divisions, int days);

    // Destructor: releases memory for dynamically allocated event objects
    ~Campaign();

    // initialises all parties, leaders, and divisions; randomises data
    void setup();

    // simulates the campaign phase — runs daily events
    void run();

    // performs the election phase — computes scores and prints results
    void results();
};

#endif 
