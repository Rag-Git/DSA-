#pragma once
#include <vector>

/*
    Class to implement a heap with general comparison function
*/

template <typename T, typename Compare>
class Heap {
public:
    /*
        Initializes a heap with a comparison function
        Details of Comparison Function:
            The comparison function should take in two arguments and return a boolean value
            If the comparison function returns True, it means that the first argument is to be considered smaller than the second argument
            If the comparison function returns False, it means that the first argument is to be considered greater than or equal to the second argument
        Time Complexity:
            O(n) where n is the number of elements in init_array
    */
    Heap(Compare comparison_function, const std::vector<T>& init_array);

    /*
        Inserts a value into the heap
        Time Complexity:
            O(log(n)) where n is the number of elements currently in the heap
    */
    void insert(const T& value);

    /*
        Extracts the value from the top of heap, i.e. removes it from heap
        Time Complexity:
            O(log(n)) where n is the number of elements currently in the heap
    */
    T extract();

    /*
        Returns the value at the top of heap
        Time Complexity:
            O(1)
    */
    T top() const;

    /*
        Returns the number of elements in the heap
    */
    int size() const;

    /*
        You can add more functions if you want to
    */

private:
    // Internal data members (like vector to store heap elements)
};
