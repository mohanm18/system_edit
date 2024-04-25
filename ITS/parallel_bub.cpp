#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <omp.h>

using namespace std;
using namespace std::chrono;

// Sequential bubble sort
void sequentialBubbleSort(vector<int>& arr) {

    int n = arr.size();
    for(int i = 0; i < n; ++i){    
        // #pragma omp for
        for (int j = 1; j < n; j += 2){//odd
        if (arr[j-1] > arr[j])
        {
          swap(arr[j], arr[j - 1]);
        }
    }

    // Synchronize
    // #pragma omp barrier

    //Sort even indexed numbers
    // #pragma omp for
    for (int j = 2; j < n; j += 2){//even
      if (arr[j-1] > arr[j])
      {
        swap(arr[j], arr[j - 1]);
      }
    }
  }


    // int n = arr.size();
    // for (int i = 0; i < n - 1; ++i) {
    //     for (int j = 0; j < n - i - 1; ++j) {
    //         if (arr[j] > arr[j + 1]) {
    //             swap(arr[j], arr[j + 1]);
    //         }
    //     }
    // }
}

// Parallel bubble sort
void parallelBubbleSort(vector<int>& arr) {
    int n = arr.size();
    for(int i = 0; i < n; ++i){    
        #pragma omp for
        for (int j = 1; j < n; j += 2){
        if (arr[j] < arr[j-1])
        {
          swap(arr[j], arr[j - 1]);
        }
    }

    // Synchronize
    #pragma omp barrier

    //Sort even indexed numbers
    #pragma omp for
    for (int j = 2; j < n; j += 2){
      if (arr[j] < arr[j-1])
      {
        swap(arr[j], arr[j - 1]);
      }
    }
  }
}

int main() {
    const int n = 10000; // Size of array
    vector<int> arr(n), arr_copy(n);

    // Generate random array
    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % n;
    }

    // Copy array for parallel sort
    copy(arr.begin(), arr.end(), arr_copy.begin());

    // Measure sequential bubble sort time
    auto start_time = high_resolution_clock::now();
    sequentialBubbleSort(arr);
    auto end_time = high_resolution_clock::now();
    auto sequential_time = duration_cast<duration<double>>(end_time - start_time).count();

    // Measure parallel bubble sort time
    start_time = high_resolution_clock::now();
    parallelBubbleSort(arr_copy);
    end_time = high_resolution_clock::now();
    auto parallel_time = duration_cast<duration<double>>(end_time - start_time).count();


    // cout << "PARA_SORT array: " << endl;
    // for (int i = 0; i < n; ++i) {
    //     cout<<arr_copy[i]<< " ";
    // }

    // Output execution times
    cout << "Sequential bubble sort time: " << sequential_time << " seconds" << endl;
    cout << "Parallel bubble sort time: " << parallel_time << " seconds" << endl;

    // Verify correctness of sorting
    for (int i = 0; i < n; ++i) {
        if (arr[i] != arr_copy[i]) {
            cout << "Error: Sorting failed!" << endl;
            return 1;
        }
    }

    cout << "Sorting successful!" << endl;

    return 0;
}
