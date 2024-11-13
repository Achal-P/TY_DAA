/*To study TSP using Branch and Bound algorithm*/
#include <iostream> 
#include <climits> // for INT_MAX 
using namespace std; 

#define MAX_V 10         // Maximum number of cities 
int graph[MAX_V][MAX_V]; // Adjacency matrix 
int n;                   // Number of cities 

struct Node 
{ 
    int level;       // Current level (city index) 
    int cost;        // Cost of path so far 
    int bound;       // Lower bound of the node 
    int path[MAX_V]; // Store the path taken 
}; 

// Function to calculate the lower bound for the given node 
int calculateBound(Node &u) 
{ 
    int bound = 0;
    bool visited[MAX_V] = {false}; 
    for (int i = 0; i < u.level; i++) 
    { 
        visited[u.path[i]] = true; 
    } 

    // Add minimum cost of outgoing edges for each unvisited city 
    for (int i = 0; i < n; i++) 
    { 
        if (!visited[i]) 
        { 
            int minEdge = INT_MAX; 
            for (int j = 0; j < n; j++) 
            { 
                if (i != j && !visited[j]) 
                { 
                    minEdge = min(minEdge, graph[i][j]); 
                } 
            } 
            if (minEdge != INT_MAX) 
            { 
                bound += minEdge; 
            } 
        } 
    } 
    bound += u.cost; 
    return bound; 
} 

// Branch and Bound TSP
void branchAndBound() 
{ 
    Node minNode; // To keep track of the minimum cost node 
    minNode.level = 0; 
    minNode.cost = 0; 
    minNode.path[0] = 0;       // Start from the first city 
    Node queue[MAX_V * MAX_V]; // Static array for nodes 
    int front = 0, rear = 0;   // Queue pointers 
    queue[rear++] = minNode; 
    minNode.bound = calculateBound(minNode); 
    int minCost = INT_MAX;
    int bestPath[MAX_V]; // To store the optimal path

    while (front < rear) 
    { 
        // Remove the node with the minimum bound from the queue 
        Node currentNode = queue[front++]; 

        // If the level is n - 1, all cities are visited 
        if (currentNode.level == n - 1) 
        { 
            // Cost to return to the starting city 
            int totalCost = currentNode.cost + graph[currentNode.path[currentNode.level]][0];
            
            if (totalCost < minCost) 
            {
                minCost = totalCost;
                // Update the best path
                for (int i = 0; i <= currentNode.level; i++) 
                {
                    bestPath[i] = currentNode.path[i];
                }
                bestPath[currentNode.level + 1] = 0; // Return to the start city
            }
            continue; 
        }

        // Explore further nodes
        for (int i = 0; i < n; i++) 
        { 
            // Check if city 'i' is already visited in the current path
            bool visited[MAX_V] = {false};
            for (int j = 0; j <= currentNode.level; j++) {
                visited[currentNode.path[j]] = true;
            }

            if (!visited[i] && graph[currentNode.path[currentNode.level]][i] != 0) 
            {
                Node newNode;
                newNode.level = currentNode.level + 1;
                newNode.cost = currentNode.cost + graph[currentNode.path[currentNode.level]][i];

                // Copy the path so far
                for (int j = 0; j <= currentNode.level; j++) 
                {
                    newNode.path[j] = currentNode.path[j];
                }
                newNode.path[newNode.level] = i;

                newNode.bound = calculateBound(newNode);

                // If the bound is less than the current minimum cost 
                if (newNode.bound < minCost) 
                { 
                    queue[rear++] = newNode;
                }
            }
        }
    }

    // Print the minimum cost and path
    cout << "Minimum cost to visit all cities: " << minCost << endl;
    cout << "Path: ";
    for (int i = 0; i <= n; i++) 
    {
        cout << bestPath[i] + 1 << (i < n ? " -> " : ""); // Adding 1 to make the path 1-indexed for clarity
    }
    cout << endl;
} 

int main() 
{ 
    cout << "Enter the number of cities: "; 
    cin >> n; 
    cout << "Enter the adjacency matrix (distance between cities):" << endl; 
    for (int i = 0; i < n; i++) 
    { 
        for (int j = 0; j < n; j++) 
        { 
            cin >> graph[i][j]; 
        } 
    } 
    branchAndBound(); 
    return 0; 
} 
/* OUTPUT:
Enter the number of cities: 4
Enter the adjacency matrix (distance between cities):
0 10 15 20
10 0 35 25
15 35 0 30
20 25 30 0
Minimum cost to visit all cities: 80
Path: 1 -> 2 -> 4 -> 3 -> 1 */