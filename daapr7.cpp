/*write a program to solve the n-queens problem using backtracking.*/
#include <iostream>
#include <vector>
using namespace std;

// Function to print the board with queens placed
void printBoard(const vector<vector<int>>& board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << (board[i][j] ? "Q " : ". ");
        }
        cout << endl;
    }
    cout << "---------------------------" << endl;
}

// Function to check if placing a queen at board[row][col] is safe
bool isSafe(const vector<vector<int>>& board, int row, int col, int n) {
    // Check this row on the left side
    for (int i = 0; i < col; i++) {
        if (board[row][i]) return false;
    }

    // Check upper diagonal on the left side
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) return false;
    }

    // Check lower diagonal on the left side
    for (int i = row, j = col; i < n && j >= 0; i++, j--) {
        if (board[i][j]) return false;
    }

    return true;
}

// Recursive function to solve N-Queens problem
bool solveNQueensUtil(vector<vector<int>>& board, int col, int n, int& solutionCount) {
    // If all queens are placed
    if (col == n) {
        printBoard(board, n);
        solutionCount++; // Increment the solution counter
        return true;
    }

    bool foundSolution = false;
    // Try placing queen in all rows one by one
    for (int i = 0; i < n; i++) {
        if (isSafe(board, i, col, n)) {
            // Place queen
            board[i][col] = 1;
            
            // Recur to place rest of the queens
            foundSolution = solveNQueensUtil(board, col + 1, n, solutionCount) || foundSolution;

            // If placing queen here doesn't lead to a solution then remove queen
            board[i][col] = 0;
        }
    }

    return foundSolution;
}

// Function to solve N-Queens problem
void solveNQueens(int n) {
    vector<vector<int>> board(n, vector<int>(n, 0));
    int solutionCount = 0; // Initialize the solution counter

    solveNQueensUtil(board, 0, n, solutionCount);

    if (solutionCount == 0) {
        cout << "No solution exists for " << n << " queens." << endl;
    } else {
        cout << "Total number of solutions for " << n << "-Queens Problem: " << solutionCount << endl;
    }
}

int main() {
    int n;
    cout << "Enter the number of queens (N): ";
    cin >> n;
    cout << "Solutions for " << n << "-Queens Problem:" << endl;
    solveNQueens(n);
    return 0;
}
 /*OUTPUT :
Enter the number of queens (N): 4
Solutions for 4-Queens Problem:
. . Q . 
Q . . . 
. . . Q 
. Q . . 
---------------------------
. Q . . 
. . . Q 
Q . . . 
. . Q . 
---------------------------
Total number of solutions for 4-Queens Problem: 2 */