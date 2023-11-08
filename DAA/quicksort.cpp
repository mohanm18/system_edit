#include <iostream>
using namespace std;

// In summary, the worst-case time complexity of standard Quicksort is O(n^2), 
// while the expected (average and best-case) time complexity of both standard 
// Quicksort and Randomized Quicksort is O(n log n)

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Function to partition the array using Lomuto's partition scheme
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Deterministic QuickSort
void deterministicQuickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = partition(arr, low, high);
        

        deterministicQuickSort(arr, low, pivot - 1);
        deterministicQuickSort(arr, pivot + 1, high);
    }
    
    
}

// Randomized QuickSort
int randomizedPartition(int arr[], int low, int high) {
     // Seed for random number generation
    // rand() is a built-in C/C++ function that generates a pseudo-random integer.
    // rand() % (high - low + 1) generates a random integer between 0 and high - low (inclusive).
    int random = low + rand() % (high - low + 1);
    swap(arr[random], arr[high]);
    return partition(arr, low, high);
}

void randomizedQuickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = randomizedPartition(arr, low, high);

        randomizedQuickSort(arr, low, pivot - 1);
        randomizedQuickSort(arr, pivot + 1, high);
    }
}

int main() {
    int arr[] = {5, 2, 7, 3, 1, 6, 4, 8};
    int size = sizeof(arr)/sizeof(arr[0]);
    int arr_copy[size] = {0};
 
    cout << "Original array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    
    cout<<endl;
    
    for (int i = 0; i < size; i++) {
        arr_copy[i] = arr[i] ;
    }
 
    cout<<endl;
    
    deterministicQuickSort(arr, 0, size - 1);
      cout << "D array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
   
    cout<<endl;

    // Reset the array
    for (int i = 0; i < size; i++) {
        arr[i] = arr_copy[i];
    }

    cout << "Reset array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout<<endl;

    // Time randomized QuickSort
    randomizedQuickSort(arr, 0, size - 1);
      cout << "R array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
   
   

    return 0;
}