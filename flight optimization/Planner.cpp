using namespace std;
#include "Planner.h"

Planner::Planner(const vector<Flight>& flights)  
{
    all_flights = flights;
    MAXN = -1;
    MAXM = -1;
    // n for cities
    // m for flights
    for(auto x : all_flights)
    {
        MAXN = max(MAXN , max(x.start_city , x.end_city));
        MAXM = max(MAXM , x.flight_no);
    }
    
    from.resize(MAXN + 1);
    to.resize(MAXN + 1);

    for(auto x : all_flights)
    {
        from[x.start_city].push_back(x);
        to[x.end_city].push_back(x);
    }

    flight_graph.resize(MAXM + 1);
    
    for(auto x : all_flights)
    {
        int ending = x.end_city;
        int arriving_time = x.arrival_time;

        for(auto y : from[ending])
        {
            if(y.departure_time >= arriving_time + 20)
            {
                flight_graph[x.flight_no].push_back(y);
            }
        }
    }
}

vector<Flight> Planner::least_flights_earliest_route(int start_city, int end_city, int t1, int t2) 
{
    queue<tuple<Flight , int , int>> q;
    vector<bool> vis(MAXM + 1 , 0);
    vector<int> parent(MAXM + 1 , -1);

    for(auto x : from[start_city])
    {
        if(x.departure_time >= t1 && x.departure_time <= t2)
        {
            q.push({x , 1, x.arrival_time});
            vis[x.flight_no] = 1;
            parent[x.flight_no] = -1;
        }
    }

    int best_arrival_time = INT_MAX;
    int best_flight_no = -1;
    int best_flights = INT_MAX;

    while(q.size())
    {
        auto[curr_flight , flights_taken , curr_arrival_time] = q.front();
        q.pop();

        if(curr_flight.end_city == end_city && curr_arrival_time <= t2)
        {
            if (flights_taken < best_flights || (flights_taken == best_flights && curr_arrival_time < best_arrival_time)) 
            {
                best_flights = flights_taken;
                best_arrival_time = curr_arrival_time;
                best_flight_no = curr_flight.flight_no;
            }
        }

        for(auto y : flight_graph[curr_flight.flight_no])
        {
            if(!vis[y.flight_no] && y.departure_time >= curr_arrival_time + 20 && y.departure_time <= t2)
            {
                vis[y.flight_no] = 1;
                parent[y.flight_no] = curr_flight.flight_no;
                q.push({y , flights_taken + 1 , y.arrival_time});
            }
        }
    }

    if (best_flight_no == -1) return {};

    vector<Flight> route;
    int cur = best_flight_no;

    while (cur != -1)
    {
        for (const Flight& f : to[end_city])
        {
            if (f.flight_no == cur)
            {
                route.push_back(f);
                end_city = f.start_city;
                break;
            }
        }

        cur = parent[cur];
    }
    reverse(route.begin(),route.end());
    return route;
}

vector<Flight> Planner::cheapest_route(int start_city, int end_city, int t1, int t2) {
    using State = pair<int , Flight>;
    auto cmp = [](const State &a, const State &b) 
    {
        return a.first > b.first;  // Only compare on `fare`, not the `Flight` itself
    };
    priority_queue<State, vector<State>, decltype(cmp)> q(cmp);
    vector<int> fare(MAXM + 1, INT_MAX);
    vector<int> parent(MAXM + 1, -1);
    vector<bool> vis(MAXM + 1, 0);

    for(auto y : from[start_city])
    {
        if(y.departure_time >= t1 && y.departure_time <= t2)
        {
            fare[y.flight_no] = y.fare;
            q.push({y.fare , y});
        }
    }

    int best_flight_no = -1;
    int best_cost = INT_MAX;

    while(q.size())
    {
        auto[curr_fare , curr] = q.top();
        q.pop();

        if(vis[curr.flight_no])     continue;
        vis[curr.flight_no] = 1;

        if(curr.end_city == end_city && curr.arrival_time <= t2)
        {
            if(curr_fare < best_cost)
            {
                best_cost = curr_fare;
                best_flight_no = curr.flight_no;
            }
        }

        for(auto y : flight_graph[curr.flight_no])
        {
            if(y.departure_time >= curr.arrival_time + 20 && y.departure_time <= t2)
            {
                int new_fare = curr_fare + y.fare;
                if(new_fare < fare[y.flight_no])
                {
                    fare[y.flight_no] = new_fare;
                    parent[y.flight_no] = curr.flight_no;
                    q.push({new_fare,y});
                }
            }
        }
    }
    if (best_flight_no == -1) return {};

    vector<Flight> route;
    int cur = best_flight_no;
    while (cur != -1) {
        route.push_back(all_flights[cur]);
        cur = parent[cur];
    }

    reverse(route.begin(), route.end());
    return route;
}

vector<Flight> Planner::least_flights_cheapest_route(int start_city, int end_city, int t1, int t2) {
    using State = tuple<int , int , Flight>;
    auto cmp = [](const State &a , const State &b)
    {
        if(get<0>(a) != get<0>(b))  return get<0>(a) > get<0>(b);
        return get<1>(a) > get<1>(b);
    };

    priority_queue<State , vector<State> , decltype(cmp)> q(cmp);

    vector<pair<int,int>> dist(MAXM + 1, {INT_MAX, INT_MAX});
    vector<int> parent(MAXM + 1 , -1);

    for(auto x : from[start_city])
    {
        if(x.departure_time >= t1 && x.departure_time <= t2)
        {
            dist[x.flight_no] = {1 , x.fare};
            q.push({1 , x.fare , x});
        }
    }

    int best_flight_number = -1;
    pair<int,int> best_pair = {INT_MAX , INT_MAX};

    while(q.size())
    {
        auto [num_flights_taken , total_fare , curr_flight] = q.top();
        q.pop();

        if(curr_flight.end_city == end_city && curr_flight.arrival_time <= t2)
        {
            pair<int,int> opn = {num_flights_taken,total_fare};
            if(opn < best_pair)
            {
                best_pair = opn;
                best_flight_number = curr_flight.flight_no;
            }
        }

        for(auto y : flight_graph[curr_flight.flight_no])
        {
            if(y.departure_time <= t2 && y.departure_time >= curr_flight.departure_time + 20)
            {
                int next_flight_num = num_flights_taken + 1;
                int next_fare = total_fare + y.fare;
                if(dist[y.flight_no] > make_pair(next_flight_num , next_fare))
                {
                    dist[y.flight_no] = {next_flight_num , next_fare};
                    parent[y.flight_no] = curr_flight.flight_no;
                    q.push({next_flight_num , next_fare , y});
                }
            }
        }
    }

    if(best_flight_number != -1)
    {
        vector<Flight> route;
        int cur = best_flight_number;
        while(cur != -1)
        {
            route.push_back(all_flights[cur]);
            cur = parent[cur];
        }

        reverse(route.begin(),route.end());
        return route;
    }

    return {};

}
