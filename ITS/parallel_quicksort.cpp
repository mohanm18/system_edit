#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <omp.h>

using namespace std;
using namespace std::chrono;

// Partition function for quick sort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Sequential quick sort
void sequentialQuickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        sequentialQuickSort(arr, low, pi - 1);
        sequentialQuickSort(arr, pi + 1, high);
    }
}

// Parallel quick sort
void parallelQuickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
#pragma omp parallel sections
        {
#pragma omp section
            parallelQuickSort(arr, low, pi - 1);
#pragma omp section
            parallelQuickSort(arr, pi + 1, high);
        }
    }
}

int main() {

     const int n = 20;
    vector<int> arr(n), arr_copy(n);
    srand(time(NULL));
    for(int i = 0; i<n; i++)
    {
        arr[i] = rand() % n;
    }

    cout << "Original array: " << endl;
    for (int i = 0; i < n; ++i) {
        cout<<arr[i]<< " ";
    }

    copy(arr.begin(), arr.end(), arr_copy.begin());

    auto start = high_resolution_clock::now();
    sequentialQuickSort(arr, 0, n-1);
    auto stop = high_resolution_clock::now();
    auto seq_time = duration_cast<duration<double>>(stop-start).count();

    start = high_resolution_clock::now();
    parallelQuickSort(arr_copy, 0, n-1);
    stop = high_resolution_clock::now();
    auto parallel_time = duration_cast<duration<double>>(stop-start).count();

    cout<<"\nSequential Time: "<<seq_time<<" secs"<<endl;
    cout<<"\nParallel Time: "<<parallel_time<<" secs"<<endl;

    cout << "SEQSORT array: " << endl;
    for (int i = 0; i < n; ++i) {
        cout<<arr[i]<< " ";
    }

    cout << "PARA_SORT array: " << endl;
    for (int i = 0; i < n; ++i) {
        cout<<arr_copy[i]<< " ";
    }

    for(int i = 0; i<n; i++)
    {
        if(arr[i] != arr_copy[i])
        {
            cout<<"Arrays are not same!!";
        }
        break;
    }
    return 0;   
    

}
