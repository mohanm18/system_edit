#include<iostream>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<algorithm>
#include<omp.h>
#include<chrono>

using namespace std;
using namespace std::chrono;


void merge(vector<int> &arr, int l, int m, int r)
{
    int n1 = m-l+1;
    int n2 = r-m;

    vector<int> L(n1), R(n2);

    for(int i = 0; i<n1; i++)
    {
        L[i] = arr[l+i];
    }

    for(int j = 0; j<n2; j++)
    {
        R[j] = arr[m+j+1];
    }

    int i = 0, j = 0, k = l;

    while(i<n1 && j<n2)
    {
        if(L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i<n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j<n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
    
}

void sequential_mergesort(vector<int> &arr, int l, int r)
{
    if(l<r)
    {
        int m = l+(r-l)/2;
        sequential_mergesort(arr, l, m);
        sequential_mergesort(arr, m+1, r);

        merge(arr, l, m, r);
    }
    
}


void parallel_mergesort(vector<int> &arr, int l, int r)
{
    if(l<r)
    {
        int m = l+(r-l)/2;
        #pragma omp parallel sections
        {
            #pragma omp section
            sequential_mergesort(arr, l, m);
            #pragma omp section
            sequential_mergesort(arr, m+1, r);
        }

        merge(arr, l, m, r); 
    }
    // merge(arr, l, m, r);
}

int main()
{

    const int n = 1500000;
    vector<int> arr(n), arr_copy(n);

    srand(time(NULL));
    for(int i = 0; i<n; i++)
    {
        arr[i] = rand() % n;
    }

    copy(arr.begin(), arr.end(), arr_copy.begin());

    auto start_time = high_resolution_clock::now();
    sequential_mergesort(arr, 0, n-1);
    auto stop_time = high_resolution_clock::now();
    auto sequential_time = duration_cast<duration<double>>(stop_time - start_time).count();


    start_time = high_resolution_clock::now();
    parallel_mergesort(arr_copy, 0, n-1);
    stop_time = high_resolution_clock::now();
    auto parallel_time = duration_cast<duration<double>>(stop_time - start_time).count();

    cout<<"\nSequential Time: "<<sequential_time<<" secs"<<endl;
    cout<<"\nParallel Time: "<<parallel_time<<" secs"<<endl;

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




