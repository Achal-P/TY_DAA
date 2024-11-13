/*develop a program to solve a fractional kanpsack problem using greedy method*/
#include <iostream>
#include <vector>
#include <algorithm> // For std::sort

using namespace std;

// Structure to store weight and value of items
struct Item {
    int weight;
    int value;
};

// Comparator function to sort items by value-to-weight ratio
bool compare(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

// Function to solve the Fractional Knapsack problem using Greedy method
double fractionalKnapsack(int capacity, vector<Item>& items) {
    // Sort items by value-to-weight ratio in descending order
    sort(items.begin(), items.end(), compare);

    double maxValue = 0.0; // Maximum value in knapsack

    // Loop through all items
    for (const Item& item : items) {
        if (capacity >= item.weight) {
            // If item can be taken completely
            capacity -= item.weight;
            maxValue += item.value;
        } else {
            // If only part of the item can be taken
            maxValue += item.value * ((double)capacity / item.weight);
            break; // Knapsack is full
        }
    }

    return maxValue;
}

int main() {
    int n, capacity;

    // Input the number of items
    cout << "Enter the number of items: ";
    cin >> n;

    // Input the capacity of the knapsack
    cout << "Enter the capacity of the knapsack: ";
    cin >> capacity;

    vector<Item> items(n);

    // Input weights and values of the items
    cout << "Enter the weights and values of the items:\n";
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << " - Weight: ";
        cin >> items[i].weight;
        cout << "        Value: ";
        cin >> items[i].value;
    }

    // Call the fractionalKnapsack function and print the result
    double maxValue = fractionalKnapsack(capacity, items);
    cout << "The maximum value that can be obtained in the knapsack is: " << maxValue << endl;

    return 0;
}
/*OUTPUT:
Enter the number of items: 3
Enter the capacity of the knapsack: 40
Enter the weights and values of the items:
Item 1 - Weight: 20
        Value: 30
Item 2 - Weight: 25
        Value: 40
Item 3 - Weight: 10
        Value: 35
The maximum value that can be obtained in the knapsack is: 82.5*/
