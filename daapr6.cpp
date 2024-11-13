/*develop a program to implement OBST using dynamic programming.*/
#include <iostream>
#include <vector>
#include <limits.h>
#include <memory>
using namespace std;

// Node structure for the binary tree
struct Node {
    int key;
    shared_ptr<Node> left;
    shared_ptr<Node> right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

// Function to calculate the sum of frequencies for keys in a given range
int sumFreq(const vector<int>& freq, int i, int j) {
    int sum = 0;
    for (int k = i; k <= j; k++) {
        sum += freq[k];
    }
    return sum;
}

// Function to print a tree structure
void printTree(const shared_ptr<Node>& root, int level = 0) {
    if (root == nullptr) return;
    printTree(root->right, level + 1);
    cout << string(level * 4, ' ') << root->key << endl;
    printTree(root->left, level + 1);
}

// Dynamic programming function to calculate the minimum cost of OBST
void optimalBST(const vector<int>& keys, const vector<int>& freq, vector<vector<int>>& cost, vector<vector<int>>& root, int n) {
    for (int i = 0; i < n; i++) {
        cost[i][i] = freq[i];
        root[i][i] = i;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            cost[i][j] = INT_MAX;
            int fsum = sumFreq(freq, i, j);

            for (int r = i; r <= j; r++) {
                int c = ((r > i) ? cost[i][r - 1] : 0) + ((r < j) ? cost[r + 1][j] : 0) + fsum;
                if (c < cost[i][j]) {
                    cost[i][j] = c;
                    root[i][j] = r;
                }
            }
        }
    }
}

// Recursive function to generate all possible BSTs based on root table
shared_ptr<Node> constructTree(const vector<int>& keys, vector<vector<int>>& root, int i, int j) {
    if (i > j) return nullptr;
    int r = root[i][j];
    shared_ptr<Node> node = make_shared<Node>(keys[r]);
    node->left = constructTree(keys, root, i, r - 1);
    node->right = constructTree(keys, root, r + 1, j);
    return node;
}

int main() {
    int n;
    cout << "Enter the number of keys: ";
    cin >> n;

    vector<int> keys(n);
    vector<int> freq(n);

    cout << "Enter the keys:\n";
    for (int i = 0; i < n; i++) {
        cin >> keys[i];
    }

    cout << "Enter the frequencies:\n";
    for (int i = 0; i < n; i++) {
        cin >> freq[i];
    }

    vector<vector<int>> cost(n, vector<int>(n, 0));
    vector<vector<int>> root(n, vector<int>(n, -1));

    // Compute the cost table and root table
    optimalBST(keys, freq, cost, root, n);

    cout << "\nThe minimum cost of constructing the Optimal BST is: " << cost[0][n - 1] << endl;

    // Construct and display the optimal BST
    shared_ptr<Node> optimalTree = constructTree(keys, root, 0, n - 1);
    cout << "\nOptimal BST Structure:\n";
    printTree(optimalTree);

    return 0;
}
/*OUTPUT :
Enter the number of keys: 3
Enter the keys:
10
12
20
Enter the frequencies:
34
8
50

The minimum cost of constructing the Optimal BST is: 142

Optimal BST Structure:
20
        12
    10 */
