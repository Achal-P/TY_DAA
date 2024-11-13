/*develop a program to implement graph coloring problem using backtracking*/
#include <iostream>
#include <string>
using namespace std;

#define MAX 100  // Maximum number of vertices, adjust as needed

// Function to check if the current color assignment is safe for vertex v
bool isSafe(int v, int graph[MAX][MAX], int color[], int c, int V) {
    for (int i = 0; i < V; i++) {
        // Check if there is an edge between vertex v and vertex i, and if both vertices have the same color
        if (graph[v][i] && color[i] == c) {
            return false;  // Not safe to color vertex v with color c
        }
    }
    return true;  // Safe to color vertex v with color c
}

// Recursive function to solve the graph coloring problem using backtracking
bool graphColoringUtil(int graph[MAX][MAX], int m, int color[], int v, int V) {
    // Base case: If all vertices are assigned a color, return true
    if (v == V) {
        return true;
    }

    // Try different colors for the current vertex
    for (int c = 1; c <= m; c++) {
        // Check if assigning color c to vertex v is safe
        if (isSafe(v, graph, color, c, V)) {
            color[v] = c;  // Assign color c to vertex v

            // Recur to assign colors to the rest of the vertices
            if (graphColoringUtil(graph, m, color, v + 1, V)) {
                return true;
            }

            // If assigning color c doesn't lead to a solution, backtrack
            color[v] = 0;  // Remove color assignment
        }
    }

    // If no color can be assigned to this vertex, return false
    return false;
}

// Function to solve the m-coloring problem with color names
bool graphColoring(int graph[MAX][MAX], int m, int V, string colorNames[]) {
    int color[MAX];  // Array to store the color assignment for each vertex
    for (int i = 0; i < V; i++) {
        color[i] = 0;  // Initialize all vertices as uncolored (0)
    }

    // Call the utility function to solve the problem
    if (!graphColoringUtil(graph, m, color, 0, V)) {
        cout << "Solution does not exist\n";
        return false;
    }

    // Print the solution with color names
    cout << "Solution exists: Following are the assigned colors\n";
    for (int i = 0; i < V; i++) {
        cout << "Vertex " << i << " --> Color " << colorNames[color[i] - 1] << endl;
    }
    return true;
}

// Main function to test the graph coloring program with user input and color names
int main() {
    int V, E, m;
    int graph[MAX][MAX] = {0};  // Adjacency matrix initialized to 0

    // Taking user input
    cout << "Enter the number of vertices: ";
    cin >> V;

    cout << "Enter the number of edges: ";
    cin >> E;

    cout << "Enter the edges (pair of vertices for each edge):\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;  // Input the two vertices of an edge
        graph[u][v] = 1;
        graph[v][u] = 1;  // Since the graph is undirected
    }

    cout << "Enter the number of colors: ";
    cin >> m;

    // Array to store color names
    string colorNames[MAX];
    cout << "Enter the names of the " << m << " colors:\n";
    for (int i = 0; i < m; i++) {
        cout << "Color " << i + 1 << ": ";
        cin >> colorNames[i];
    }

    // Solve the graph coloring problem
    graphColoring(graph, m, V, colorNames);

    return 0;
}
/*OUTPUT :
Enter the number of vertices: 4
Enter the number of edges: 5
Enter the edges (pair of vertices for each edge):
0 1
0 3
1 2
1 3
2 3
Enter the number of colors: 3
Enter the names of the 3 colors:
Color 1: Red 
Color 2: Blue 
Color 3: Green
Solution exists: Following are the assigned colors
Vertex 0 --> Color Red
Vertex 1 --> Color Blue
Vertex 2 --> Color Red
Vertex 3 --> Color Green
=== Code Execution Successful === */
