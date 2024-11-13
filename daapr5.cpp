/*develop a program to implement 0/1 knapsack problem using dynamic programming*/
#include <iostream>
#include <vector>
#include <algorithm> // For std::max
#include <iomanip>   // For std::setw

using namespace std;

// Function to generate and print the DP table
void printTable(const vector<vector<int>>& dp, int n, int capacity) {
    cout << "DP Table (Items/Weights):\n";
    cout << setw(10) << "Items\\Weight";
    for (int w = 0; w <= capacity; w++) {
        cout << setw(6) << w; // Print the weight as columns
    }
    cout << endl;

    for (int i = 0; i <= n; i++) {
        if (i == 0)
            cout << setw(10) << "0"; // Header for row 0 (no items)
        else
            cout << setw(10) << i; // Print the item number

        for (int w = 0; w <= capacity; w++) {
            cout << setw(6) << dp[i][w]; // Print the DP values for each item and weight
        }
        cout << endl;
    }
}

// Function to solve the 0/1 Knapsack problem using Dynamic Programming
int knapsack(int capacity, const vector<int>& weights, const vector<int>& values, int n) {
    // Create a DP table to store the maximum value for each weight
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    // Build the DP table
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            // If the weight of the current item is less than or equal to the current capacity
            if (weights[i - 1] <= w) {
                // Choose the maximum value between including the item or not including it
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            } else {
                // If the item cannot be included, carry forward the previous value
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Print the DP table
    printTable(dp, n, capacity);

    // The maximum value is found in the last cell of the table
    return dp[n][capacity];
}

int main() {
    int n, capacity;

    // Input the number of items
    cout << "Enter the number of items: ";
    cin >> n;

    // Input the capacity of the knapsack
    cout << "Enter the capacity of the knapsack: ";
    cin >> capacity;

    vector<int> weights(n);
    vector<int> values(n);

    // Input weights and values of the items
    cout << "Enter the weights of the items:\n";
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }

    cout << "Enter the values of the items:\n";
    for (int i = 0; i < n; i++) {
        cin >> values[i];
    }

    // Call the knapsack function and print the result
    int maxValue = knapsack(capacity, weights, values, n);
    cout << "The maximum value that can be obtained in the knapsack is: " << maxValue << endl;

    return 0;
}
/*OUTPUT :
Enter the number of items: 3
Enter the capacity of the knapsack: 4
Enter the weights of the items:
1 2 2
Enter the values of the items:
18 16 6
DP Table (Items/Weights):
Items\Weight     0     1     2     3     4
         0     0     0     0     0     0
         1     0    18    18    18    18
         2     0    18    18    34    34
         3     0    18    18    34    34
The maximum value that can be obtained in the knapsack is: 34
=== Code Execution Successful ===*/