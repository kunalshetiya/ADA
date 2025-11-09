#include <stdio.h>
#include <stdbool.h>

#define MAX 10  // maximum board size

// Function to print the chessboard
void printSolution(int board[MAX][MAX], int N) {
    printf("\nOne of the possible solutions:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", board[i][j] ? 'Q' : '.'); // Q = Queen, . = Empty
        }
        printf("\n");
    }
}

// Check if placing a queen at board[row][col] is safe
bool isSafe(int board[MAX][MAX], int row, int col, int N) {
    int i, j;

    // Check column above
    for (i = 0; i < row; i++)
        if (board[i][col])
            return false;

    // Check upper left diagonal
    for (i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check upper right diagonal
    for (i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++)
        if (board[i][j])
            return false;

    return true;
}

// Recursive function to solve N-Queens problem
bool solveNQUtil(int board[MAX][MAX], int row, int N) {
    // Base case: if all queens are placed
    if (row == N) {
        printSolution(board, N);
        return true;
    }

    bool res = false; // to check if at least one solution exists

    // Try placing queen in all columns of current row
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col, N)) {
            board[row][col] = 1; // place queen

            // Recur to place the rest
            res = solveNQUtil(board, row + 1, N) || res;

            // Backtrack (remove queen)
            board[row][col] = 0;
        }
    }

    return res;
}

// Main function to initiate solving process
void solveNQ(int N) {
    int board[MAX][MAX] = {0};

    if (!solveNQUtil(board, 0, N))
        printf("\nNo solution exists for N = %d\n", N);
}

// Driver code
int main() {
    int N;
    printf("Enter the number of queens (N): ");
    scanf("%d", &N);
    solveNQ(N);
    return 0;
}