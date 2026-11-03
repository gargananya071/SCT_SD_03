#include <iostream>
using namespace std;

// Size of the Sudoku grid (9x9)
const int N = 9;

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    cout << "\n---------------------\n";
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++)
            cout << grid[r][c] << " ";
        cout << endl;
    }
    cout << "---------------------\n";
}

// Function to check if it's safe to place a number
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check row
    for (int x = 0; x < 9; x++)
        if (grid[row][x] == num)
            return false;

    // Check column
    for (int x = 0; x < 9; x++)
        if (grid[x][col] == num)
            return false;

    // Check 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Function to solve Sudoku using Backtracking
bool solveSudoku(int grid[N][N], int row, int col) {
    if (row == N - 1 && col == N)
        return true;

    if (col == N) {
        row++;
        col = 0;
    }

    if (grid[row][col] > 0)
        return solveSudoku(grid, row, col + 1);

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid, row, col + 1))
                return true;
        }
        grid[row][col] = 0; // Backtrack
    }

    return false;
}

int main() {
    int grid[N][N];

    cout << "Enter the Sudoku puzzle row by row (9 numbers per row, use 0 for empty cells):\n";
    
    // Taking input from user
    for (int i = 0; i < N; i++) {
        cout << "Enter row " << i + 1 << ": ";
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
        }
    }

    cout << "\nYour Entered Sudoku Puzzle:";
    printGrid(grid);

    if (solveSudoku(grid, 0, 0)) {
        cout << "\nSuccessfully Solved Sudoku Puzzle:";
        printGrid(grid);
    } else {
        cout << "\nNo solution exists for the given Sudoku puzzle!" << endl;
    }

    return 0;
}