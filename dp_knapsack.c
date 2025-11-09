#include <stdio.h>

// Function to find the greater of two numbers
int findMax(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

// Function to solve 0/1 Knapsack using Dynamic Programming
int knapSack(int capacity, int weight[], int value[], int n) {
    int dp[n + 1][capacity + 1];

    // Step 1: Build DP table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            // Base case: 0 items or 0 capacity
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            } 
            // If current item's weight <= current capacity
            else if (weight[i - 1] <= w) {
                int includeItem = value[i - 1] + dp[i - 1][w - weight[i - 1]];
                int excludeItem = dp[i - 1][w];
                dp[i][w] = findMax(includeItem, excludeItem);
            } 
            // If item can't be included (too heavy)
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Step 2: Backtrack to find items included
    int result = dp[n][capacity];
    int remainingCapacity = capacity;

    printf("\nItems included in the bag:\n");
    for (int i = n; i > 0 && result > 0; i--) {
        if (result != dp[i - 1][remainingCapacity]) {
            printf("Item %d -> Weight = %d, Value = %d\n", i, weight[i - 1], value[i - 1]);
            result = result - value[i - 1];
            remainingCapacity = remainingCapacity - weight[i - 1];
        }
    }

    // Step 3: Print DP Table (for understanding)
    printf("\nDP Table:\n");
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            printf("%3d ", dp[i][w]);
        }
        printf("\n");
    }

    return dp[n][capacity];
}

// Main Function
int main() {
    int n, capacity;

    printf("Enter number of items: ");
    scanf("%d", &n);

    int value[n], weight[n];

    printf("Enter values (profits): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &value[i]);
    }

    printf("Enter weights: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &weight[i]);
    }

    printf("Enter knapsack capacity: ");
    scanf("%d", &capacity);

    int maxValue = knapSack(capacity, weight, value, n);
    printf("\nMaximum value that can be obtained = %d\n", maxValue);

    return 0;
}