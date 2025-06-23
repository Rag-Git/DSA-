#pragma once
#include <vector>
#include "Treasure.h"

/*
    Class to implement a crewmate
*/

class CrewMate {
public:
    /*
        Initializes the crewmate
    */
    CrewMate();

    /*
        Add more methods if required
    */

    /*
        Add a treasure to this crewmate's list
    */
    void add_treasure(const Treasure& treasure);

private:
    std::vector<Treasure> treasure;
    bool empty;
};
