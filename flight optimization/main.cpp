#include <iostream>
#include <vector>
#include "Flight.h"
#include "Planner.h"

using namespace std;

int main() {
    vector<Flight> flights = {
        Flight(0, 0, 0, 1, 30, 50),     // City 0 to 1
        Flight(1, 0, 0, 3, 80, 200),    // City 0 to 3
        Flight(2, 1, 40, 2, 60, 20),    // City 1 to 2
        Flight(3, 1, 50, 2, 100, 120),  // City 1 to 2
        Flight(4, 2, 120, 4, 200, 100), // City 2 to 4
        Flight(5, 3, 100, 4, 150, 500), // City 3 to 4
        Flight(6, 3, 100, 4, 250, 300)  // City 3 to 4
    };

    Planner flight_planner(flights);

    // Task 1: Fewest flights & earliest
    vector<Flight> route1 = flight_planner.least_flights_earliest_route(0, 4, 0, 300);

    // Task 2: Cheapest route
    vector<Flight> route2 = flight_planner.cheapest_route(0, 4, 0, 300);

    // Task 3: Fewest flights & cheapest
    vector<Flight> route3 = flight_planner.least_flights_cheapest_route(0, 4, 0, 300);

    // Expected answers
    vector<Flight> expected_route1 = {flights[1], flights[5]};
    vector<Flight> expected_route2 = {flights[0], flights[3], flights[4]};
    vector<Flight> expected_route3 = {flights[1], flights[6]};

    auto are_equal = [](const vector<Flight>& a, const vector<Flight>& b) {
        if (a.size() != b.size()) return false;
        for (size_t i = 0; i < a.size(); ++i)
            if (a[i].flight_no != b[i].flight_no) return false;
        return true;
    };

    if (are_equal(route1, expected_route1)) {
        cout << "Task 1 PASSED" << endl;
    } else {
        cout << "Task 1 FAILED" << endl;
    }

    if (are_equal(route2, expected_route2)) {
        cout << "Task 2 PASSED" << endl;
    } else {
        cout << "Task 2 FAILED" << endl;
    }

    if (are_equal(route3, expected_route3)) {
        cout << "Task 3 PASSED" << endl;
    } else {
        cout << "Task 3 FAILED" << endl;
    }

    return 0;
}
