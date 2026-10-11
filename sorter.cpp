#include "sorter.h"


// Merge Sort by name karna hai, needs rechecking


static void mergeByName(Resource arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Resource* leftArr = new Resource[n1];
    Resource* rightArr = new Resource[n2];

    for (int i = 0; i < n1; i++) leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++) rightArr[j] = arr[mid + 1 + j];


    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i].name <= rightArr[j].name) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;


    }
    while (i < n1) { arr[k] = leftArr[i]; i++; k++; }
    while (j < n2) { arr[k] = rightArr[j]; j++; k++; }

    delete[] leftArr;
    delete[] rightArr;
}

static void mergeSortByNameHelper(Resource arr[], int left, int right) {
    if (left >= right) return; // base case: 0 or 1 elements, already sorted hogaya hai

    int mid = left + (right - left) / 2;
    mergeSortByNameHelper(arr, left, mid);
    mergeSortByNameHelper(arr, mid + 1, right);
    mergeByName(arr, left, mid, right);

}

void mergeSortByName(Resource arr[], int n) {
    if (n <= 1) return;
    mergeSortByNameHelper(arr, 0, n - 1);
}



// Merge Sort by ID

static void mergeByID(Resource arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;


    Resource* leftArr = new Resource[n1];
    Resource* rightArr = new Resource[n2];

    for (int i = 0; i < n1; i++) leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++) rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i].id <= rightArr[j].id) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    while (i < n1) { arr[k] = leftArr[i]; i++; k++; }
    while (j < n2) { arr[k] = rightArr[j]; j++; k++; }



    delete[] leftArr;
    delete[] rightArr;
}

static void mergeSortByIDHelper(Resource arr[], int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSortByIDHelper(arr, left, mid);
    mergeSortByIDHelper(arr, mid + 1, right);

    mergeByID(arr, left, mid, right);
}

void mergeSortByID(Resource arr[], int n) {
    if (n <= 1) return;
    mergeSortByIDHelper(arr, 0, n - 1);
}


// Binary Search by ID

int binarySearchByID(Resource arr[], int n, int targetID) {

    int low = 0;

    int high = n - 1;


    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid].id == targetID) {
            return mid;
        } else if (arr[mid].id < targetID) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1; 
}