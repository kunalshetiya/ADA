#include <stdio.h>
#include <limits.h>

#define MAX 10
#define INF 999999

int n;
int cost[MAX][MAX];
int dp[1 << MAX][MAX];    // DP table: (bitmask, current city)
int nextCity[1 << MAX][MAX]; // To reconstruct path
int visited_all;

/* Recursive function to solve TSP using DP + Bitmasking */
int tsp(int mask, int pos) {
    if (mask == visited_all)
        return cost[pos][0]; // Return cost to start city

    if (dp[mask][pos] != -1)
        return dp[mask][pos];

    int ans = INF;
    int chosenCity = -1;

    for (int city = 0; city < n; city++) {
        if ((mask & (1 << city)) == 0) { // if city not visited
            int newAns = cost[pos][city] + tsp(mask | (1 << city), city);
            if (newAns < ans) {
                ans = newAns;
                chosenCity = city;
            }
        }
    }

    nextCity[mask][pos] = chosenCity; // Store next city for this state
    dp[mask][pos] = ans;
    return ans;
}

/* Function to print the path */
void printPath() {
    int mask = 1, pos = 0;

    printf("\nPath: ");
    printf("0 "); // start from city 0

    while (1) {
        int city = nextCity[mask][pos];
        if (city == -1)
            break;
        printf("-> %d ", city);
        mask |= (1 << city);
        pos = city;
    }
    printf("-> 0\n"); // return to start
}

int main() {
    printf("Enter number of cities: ");
    scanf("%d", &n);

    printf("Enter cost matrix (0 if same city):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    visited_all = (1 << n) - 1;

    // initialize DP arrays with -1
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = -1;
            nextCity[i][j] = -1;
        }
    }

    int answer = tsp(1, 0); // start from city 0 with mask 1 (only city 0 visited)

    printf("\nMinimum cost of travelling all cities = %d\n", answer);
    printPath();

    return 0;
}
