#include <stdio.h>

#define MAX 30

struct Edge {
    int u, v, w;
};

int parent[MAX];

int findParent(int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

void unionSet(int i, int j) {
    int a = findParent(i);
    int b = findParent(j);
    parent[a] = b;
}

void kruskal(int n, int e, struct Edge edges[]) {
    int i, j;
    struct Edge temp;
    int totalCost = 0, count = 0;

    // Sort edges by weight (Bubble Sort)
    for (i = 0; i < e - 1; i++) {
        for (j = 0; j < e - i - 1; j++) {
            if (edges[j].w > edges[j + 1].w) {
                temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    // Initialize parent array
    for (i = 0; i < n; i++)
        parent[i] = i;

    printf("\nEdges in the Minimum Spanning Tree (Kruskal's):\n");
    for (i = 0; i < e && count < n - 1; i++) {
        int a = findParent(edges[i].u);
        int b = findParent(edges[i].v);

        if (a != b) {
            printf("%d -- %d == %d\n", edges[i].u, edges[i].v, edges[i].w);
            totalCost += edges[i].w;
            unionSet(a, b);
            count++;
        }
    }

    printf("Total weight of MST = %d\n", totalCost);
}

int main() {
    struct Edge edges[MAX];
    int n, e, i;

    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter edges (u v w):\n");
    for (i = 0; i < e; i++)
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);

    kruskal(n, e, edges);

    return 0;
}  