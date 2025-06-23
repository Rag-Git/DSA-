#pragma once
#include<bits/stdc++.h>
using namespace std;

class Flight
{
    public : 
        int flight_no;
        int start_city;
        int departure_time;
        int end_city;
        int arrival_time;
        int fare;

        Flight(int flight_no_ , int start_city_ , int departure_time_ , int end_city_ ,
             int arrival_time_, int fare_)
        {
            flight_no = flight_no_;
            start_city = start_city_;
            departure_time = departure_time_;
            end_city = end_city_;
            arrival_time = arrival_time_;
            fare = fare_;
        }


};