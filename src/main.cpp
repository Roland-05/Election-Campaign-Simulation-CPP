#include "campaign.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: ./APE <numDivisions> <numEventDays>\n";
        return 1;
    }

    int numDivisions = std::atoi(argv[1]);
    int numDays = std::atoi(argv[2]);

    if (numDivisions < 1 || numDivisions > 10 || numDays < 1 || numDays > 30) {
        std::cout << "Error: numDivisions 1–10, numEventDays 1–30.\n";
        return 1;
    }

    Campaign election(numDivisions, numDays);
    election.setup();
    election.run();
    election.results();

    return 0;
}
