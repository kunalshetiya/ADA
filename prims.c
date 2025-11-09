#include <stdio.h>
#include <limits.h>

#define MAX 20

void prims(int cost[MAX][MAX], int n) {
    int visited[MAX] = {0};
    int totalCost = 0, edges = 0;

    visited[0] = 1; // Start from vertex 0

    printf("\nEdges in the Minimum Spanning Tree (Prim's):\n");

    while (edges < n - 1) {
        int min = INT_MAX, u = -1, v = -1;

        for (int i = 0; i < n; i++) {
            if (visited[i]) {
                for (int j = 0; j < n; j++) {
                    if (!visited[j] && cost[i][j] && cost[i][j] < min) {
                        min = cost[i][j];
                        u = i;
                        v = j;
                    }
                }
            }
        }

        if (u != -1 && v != -1) {
            printf("%d -- %d == %d\n", u, v, min);
            totalCost += min;
            visited[v] = 1;
            edges++;
        }
    }

    printf("Total weight of MST = %d\n", totalCost);
}

int main() {
    int cost[MAX][MAX], n;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter cost adjacency matrix (0 if no edge):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] == 0)
                cost[i][j] = INT_MAX; // No edge
        }
    }

    prims(cost, n);

    return 0;
}
