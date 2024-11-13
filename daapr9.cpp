/* develop a program that uses branch and bound to solve the 0/1 knapsack problem.*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Structure to represent an item
struct Item {
    double weight;
    double value;
};

// Node structure for branch and bound
struct Node {
    int level;         // Level in decision tree
    double profit;     // Total profit (value) so far
    double weight;     // Total weight so far
    double bound;      // Upper bound of maximum profit from this node
};

// Comparator function to sort items based on value/weight ratio
bool compareItems(const Item& a, const Item& b) {
    double r1 = a.value / a.weight;
    double r2 = b.value / b.weight;
    return r1 > r2;
}

// Function to calculate the upper bound of profit in the subtree rooted at 'node'
double calculateBound(Node node, int n, double W, const vector<Item>& items) {
    if (node.weight >= W) return 0;

    double profitBound = node.profit;
    int j = node.level + 1;
    double totalWeight = node.weight;

    while (j < n && totalWeight + items[j].weight <= W) {
        totalWeight += items[j].weight;
        profitBound += items[j].value;
        j++;
    }

    if (j < n) {
        profitBound += (W - totalWeight) * (items[j].value / items[j].weight);
    }

    return profitBound;
}

// Function to solve 0/1 Knapsack using Branch and Bound
double knapsackBranchAndBound(double W, const vector<Item>& items, int n) {
    vector<Item> sortedItems = items;
    sort(sortedItems.begin(), sortedItems.end(), compareItems);

    queue<Node> Q;
    Node u, v;

    u.level = -1;
    u.profit = 0;
    u.weight = 0;
    u.bound = calculateBound(u, n, W, sortedItems);
    Q.push(u);

    double maxProfit = 0;

    while (!Q.empty()) {
        u = Q.front();
        Q.pop();

        if (u.level == n - 1) continue;

        v.level = u.level + 1;

        // Case 1: Take the item at 'v.level'
        v.weight = u.weight + sortedItems[v.level].weight;
        v.profit = u.profit + sortedItems[v.level].value;

        if (v.weight <= W && v.profit > maxProfit) {
            maxProfit = v.profit;
        }

        v.bound = calculateBound(v, n, W, sortedItems);
        if (v.bound > maxProfit) {
            Q.push(v);
        }

        // Case 2: Do not take the item at 'v.level'
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = calculateBound(v, n, W, sortedItems);

        if (v.bound > maxProfit) {
            Q.push(v);
        }
    }

    return maxProfit;
}

int main() {
    int n;
    double W;
    cout << "Enter the number of items: ";
    cin >> n;

    vector<Item> items(n);
    cout << "Enter the weight and value of each item:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << " (weight value): ";
        cin >> items[i].weight >> items[i].value;
    }

    cout << "Enter the maximum capacity of the knapsack: ";
    cin >> W;

    double maxProfit = knapsackBranchAndBound(W, items, n);
    cout << "Maximum profit for the given knapsack capacity: " << maxProfit << endl;

    return 0;
}
/*OUTPUT :
Enter the number of items: 5
Enter the weight and value of each item:
Item 1 (weight value): 2 40
Item 2 (weight value): 3.14 50
Item 3 (weight value): 1.98 100
Item 4 (weight value): 5 95   
Item 5 (weight value): 3 30
Enter the maximum capacity of the knapsack: 10
Maximum profit for the given knapsack capacity: 235 */