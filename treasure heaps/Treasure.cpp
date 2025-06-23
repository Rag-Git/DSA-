#include "Treasure.h"

Treasure::Treasure(int id, int size, int arrival_time) {
    this->id = id;
    this->size = size;
    this->arrival_time = arrival_time;
    this->completion_time = -1;
}
