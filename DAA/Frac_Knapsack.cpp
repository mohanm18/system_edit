#include <iostream>
#include <vector>
#include <algorithm>
// Time Complexity: O(2^N)
// Auxiliary Space: O(N)

using namespace std;

struct Item {
    int weight;
    int profit;
    double ratio; // Profit-to-weight ratio
};

bool compareItems(const Item& item1, const Item& item2) {
    return item1.ratio > item2.ratio;
}

double fractionalKnapsack(vector<Item>& items, int capacity) {
    // Calculate profit-to-weight ratios for each item
    for (Item& item : items) {
        item.ratio = static_cast<double>(item.profit) / item.weight;
    }

    // Sort items in decreasing order of profit-to-weight ratio
    sort(items.begin(), items.end(), compareItems);

    double maxProfit = 0.0;

    for (const Item& item : items) {
        if (capacity <= 0) {
            break; // Knapsack is full
        }

        // Calculate the fraction of the item to take
        double fraction = min(1.0, static_cast<double>(capacity) / item.weight);

        // Update the profit and remaining capacity
        maxProfit += fraction * item.profit;
        capacity -= static_cast<int>(fraction * item.weight);
    }

    return maxProfit;
}

int main() {
    int n; // Number of items
    int capacity; // Knapsack weight limit

    cout << "Enter the number of items: ";
    cin >> n;
    cout << "Enter the knapsack weight limit: ";
    cin >> capacity;

    vector<Item> items(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter the profit and weight for item " << i + 1 << ": ";
        cin >> items[i].profit >> items[i].weight;
    }

    double maxProfit = fractionalKnapsack(items, capacity);

    cout << "Maximum profit that can be obtained: " << maxProfit << endl;

    return 0;
}
