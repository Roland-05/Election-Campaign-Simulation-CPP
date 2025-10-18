// events.h
// Defines all event classes that can occur during the campaign simulation.
// These events modify leaders’ or divisions’ attributes (e.g., popularity,
// stance, or population) on each campaign day. Each event inherits from
// the abstract base class Event and overrides the applyEvent() function.

#ifndef EVENTS_H
#define EVENTS_H

#include "domain.h"
#include <string>
#include <random>
#include <ctime>
#include <iostream>

// Base class: Event
// represents a generic campaign event that affects either a leader or division.
// all specific event types inherit from this and must implement applyEvent().
class Event {
protected:
    std::string eventName;  // name of the event type
    double eventProbability; // probability weight (used conceptually)
public:
    Event(std::string name, double probability);
    virtual ~Event() {} // virtual destructor ensures subclass cleanup

    std::string getName(); // returns the event’s name
    double getProbability(); // returns the event’s probability

    // Pure virtual function — must be implemented by all subclasses.
    // This defines what happens when the event is applied.
    virtual void applyEvent(Leader& leader, Division& division) = 0;
};

// PopularityChange
// randomly increases or decreases a leader’s popularity value.
// Helps simulate media coverage or public perception changes.

class PopularityChange : public Event {
public:
    PopularityChange();   // constructor sets event name/probability
    void applyEvent(Leader& leader, Division& division) override;
};

// PolicyShift
// Randomly adjusts one of the leader’s five stances on issues.
// model how a leader’s opinion might shift over a campaign.
class PolicyShift : public Event {
public:
    PolicyShift();
    void applyEvent(Leader& leader, Division& division) override;
};

// PublicOpinionShift
// Randomly adjusts one stance of a division to represent a
// population’s changing priorities or opinions over time.
class PublicOpinionShift : public Event {
public:
    PublicOpinionShift();
    void applyEvent(Leader& leader, Division& division) override;
};

// PopulationChange
// Randomly increases or decreases a division’s population value.
// reflects migration, demographic, or registration changes.
class PopulationChange : public Event {
public:
    PopulationChange();
    void applyEvent(Leader& leader, Division& division);
};

#endif 
