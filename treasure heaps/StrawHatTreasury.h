#pragma once
#include <vector>
#include "CrewMate.h"
#include "Treasure.h"
#include "Heap.h"

/*
    Class to implement the StrawHat Crew Treasury
*/

class StrawHatTreasury {
public:
    /*
        Initializes the StrawHat
        Time Complexity:
            O(m)
    */
    StrawHatTreasury(int m);

    /*
        Adds the treasure to the treasury
        Time Complexity:
            O(log(m) + log(n)) where
                m : Number of Crew Mates
                n : Number of Treasures
    */
    void add_treasure(const Treasure& treasure);

    /*
        Returns all the treasure after processing them
        Time Complexity:
            O(n(log(m) + log(n))) where
                m : Number of Crew Mates
                n : Number of Treasures
    */
    std::vector<Treasure> get_completion_time();

    /*
        You can add more methods if required
    */

private:
    // Data members like crewmates heap and list of non-empty crewmates
};
