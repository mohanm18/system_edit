#include <iostream>
#include <vector>

using namespace std;

// Function to print the N-Queens matrix
void printMatrix(const vector<vector<char>>& board, int solutionNumber) {
    cout << "Solution number " << solutionNumber << ":\n";
    for (const vector<char>& row : board) {
        for (char cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Function to check if a Queen can be placed at the given position (row, col)
bool canPlaceQueen(const vector<vector<char>>& board, int row, int col, int N) {
    // Check the row
    for (int i = 0; i < N; i++) {
        if (board[row][i] == 'Q') {
            return false;
        }
    }

    // Check the column
    for (int i = 0; i < N; i++) {
        if (board[i][col] == 'Q') {
            return false;
        }
    }

    // Check the upper-left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }

    // Check the upper-right diagonal
    for (int i = row, j = col; i >= 0 && j < N; i--, j++) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }

    return true;
}

// Function to solve the N-Queens problem using backtracking
void solveNQueens(vector<vector<char>>& board, int row, int N, int& solutionNumber) {
    if (row == N) {
        // If all Queens are placed, print the matrix and increment the solution number
        printMatrix(board, solutionNumber);
        solutionNumber++;
        return;
    }

    for (int col = 0; col < N; col++) {
        if (canPlaceQueen(board, row, col, N)) {
            board[row][col] = 'Q';
            solveNQueens(board, row + 1, N, solutionNumber);
            board[row][col] = '.';  // Backtrack
        }
    }
}

int main() {
    int N; // User-defined N
    cout << "Enter the value of N for the N-Queens problem: ";
    cin >> N;

    vector<vector<char>> board(N, vector<char>(N, '.'));

    // Place the first Queen (e.g., at the top-left corner)
    board[0][7] = 'Q';

    int solutionNumber = 1; // Initialize the solution number

    // Call the solveNQueens function to solve the N-Queens problem
    solveNQueens(board, 1, N, solutionNumber);

    return 0;
}
