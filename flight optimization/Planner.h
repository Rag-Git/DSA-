#pragma once
#include "Flight.h"

class Planner
{
    public : 
        Planner(const vector<Flight>& flights);

        vector<Flight> least_flights_earliest_route(int start_city , int end_city, int t1 , int t2);
        vector<Flight> cheapest_route(int start_city, int end_city, int t1, int t2);
        vector<Flight> least_flights_cheapest_route(int start_city, int end_city, int t1, int t2);

    private :
        vector<Flight> all_flights;
        vector<vector<Flight>> from , to , flight_graph;
        int MAXM , MAXN;
};