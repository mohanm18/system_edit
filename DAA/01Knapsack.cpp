#include<iostream>
#include<vector>
#include<algorithm>
// bottom up dp
// Time Complexity: O(N * W). where ‘N’ is the number of elements and ‘W’ is capacity. 
// Auxiliary Space: O(N * W). The use of a 2-D array of size ‘N*W’.
using namespace std;

int knapsack(int W, int n, int wt[], int p[])
{
    vector<vector<int>> val(n+1, vector<int>(W+1));

    for(int i = 0; i<=n; i++)
    {
        for(int w =0; w<=W; w++)
        {
            if(i == 0 || w == 0)
            {
                val[i][w] = 0;
            }
            else if(wt[i] <= W)
            {
                val[i][w] = max(val[i-1][w], val[i-1][w-wt[i-1]] + p[i]);
            }
            else
            {
                val[i][w] = val[i-1][w];
            }
        }
    }
    return val[n][W];
}

int main(){
    int profit[] = { 1, 2, 3}; 
    int weight[] = { 4, 5, 1 }; 
    int W = 3; 
    int n = sizeof(profit) / sizeof(profit[0]); 
 
    cout << knapsack(W, n, weight, profit); 

    return 0;
}