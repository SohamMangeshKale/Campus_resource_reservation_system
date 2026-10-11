#ifndef SORTER_H
#define SORTER_H

#include "structures.h"

// Complexity: O(n log n).
void mergeSortByName(Resource arr[], int n);


// Complexity: O(n log n).
void mergeSortByID(Resource arr[], int n);


// Complexity: O(log n).
int binarySearchByID(Resource arr[], int n, int targetID);

#endif