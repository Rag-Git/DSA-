#pragma once
using namespace std;

/*
    Class to implement a treasure
*/

class Treasure {
public:
    /*
        Initializes the treasure
    */
    Treasure(int id, int size, int arrival_time);

    int id;              // The id of the treasure (unique positive integer for each treasure)
    int size;            // The size of the treasure (positive integer)
    int arrival_time;    // The arrival time of the treasure (non-negative integer)
    int completion_time; // To be updated during processing

    /*
        You can add more methods if required
    */
};
