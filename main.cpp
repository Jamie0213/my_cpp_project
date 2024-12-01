#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#define UNASSIGNED 0
#define N 9

using namespace std;

bool FindUnassignedLocation(int grid[N][N], int &row, int &col);
bool isSafe(int grid[N][N], int row, int col, int num);

bool SolveSudoku(int grid[N][N]) {
    int row, col;
    if (!FindUnassignedLocation(grid, row, col))
        return true;

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (SolveSudoku(grid))
                return true;
            grid[row][col] = UNASSIGNED;
        }
    }
    return false;
}

bool FindUnassignedLocation(int grid[N][N], int &row, int &col) {
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == UNASSIGNED)
                return true;
    return false;
}

bool UsedInRow(int grid[N][N], int row, int num) {
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}

bool UsedInCol(int grid[N][N], int col, int num) {
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}

bool UsedInBox(int grid[N][N], int boxStartRow, int boxStartCol, int num) {
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row + boxStartRow][col + boxStartCol] == num)
                return true;
    return false;
}

bool isSafe(int grid[N][N], int row, int col, int num) {
    return !UsedInRow(grid, row, num) &&
           !UsedInCol(grid, col, num) &&
           !UsedInBox(grid, row - row % 3, col - col % 3, num) &&
           grid[row][col] == UNASSIGNED;
}

void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            cout << grid[row][col] << " ";
        cout << endl;
    }
}

void fillDiagonal(int grid[N][N]) {
    for (int i = 0; i < N; i += 3) {
        int num;
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                do {
                    num = rand() % 9 + 1;
                } while (UsedInBox(grid, i, i, num));
                grid[row + i][col + i] = num;
            }
        }
    }
}

void removeDigits(int grid[N][N], int count) {
    while (count != 0) {
        int cellId = rand() % (N * N);
        int row = cellId / N;
        int col = cellId % N;
        if (grid[row][col] != UNASSIGNED) {
            grid[row][col] = UNASSIGNED;
            count--;
        }
    }
}

void generateSudoku(int grid[N][N]) {
    srand(time(0));
    fillDiagonal(grid);
    SolveSudoku(grid);
    removeDigits(grid, 40); // Remove 40 digits to create a puzzle
}

int main() {
    int grid[N][N] = {0};
    generateSudoku(grid);
    cout << "Generated Sudoku Puzzle:" << endl;
    printGrid(grid);
    if (SolveSudoku(grid)) {
        cout << "Solved Sudoku Puzzle:" << endl;
        printGrid(grid);
    } else {
        cout << "No solution exists";
    }
    return 0;
}