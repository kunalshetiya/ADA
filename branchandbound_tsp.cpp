#include <iostream>
#include <climits>
using namespace std;

int n;                    // number of cities
int cost[10][10];         // cost matrix
int final_path[11];       // final tour
bool visited[10];         // visited cities
int final_cost = INT_MAX; // minimum cost

// Copy current path to final_path
void copyToFinal(int curr_path[]) {
    for (int i = 0; i < n; i++)
        final_path[i] = curr_path[i];
    final_path[n] = curr_path[0]; // return to start
}

// Get first minimum edge cost from city i
int firstMin(int i) {
    int min = INT_MAX;
    for (int k = 0; k < n; k++)
        if (cost[i][k] < min)
            min = cost[i][k];
    return min;
}

// Get second minimum edge cost from city i
int secondMin(int i) {
    int first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < n; j++) {
        if (cost[i][j] < first) {
            second = first;
            first = cost[i][j];
        } else if (cost[i][j] < second) {
            second = cost[i][j];
        }
    }
    return second;
}

// Recursive TSP function
void TSP(int curr_path[], int curr_cost, int level) {
    if (level == n) {
        // Return to starting city
        if (cost[curr_path[level-1]][curr_path[0]] != 0) {
            int total_cost = curr_cost + cost[curr_path[level-1]][curr_path[0]];
            if (total_cost < final_cost) {
                final_cost = total_cost;
                copyToFinal(curr_path);
            }
        }
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i] && cost[curr_path[level-1]][i] != 0) {
            
            // Calculate lower bound for pruning
            int bound = curr_cost;
            if (level == 1)
                bound += firstMin(curr_path[0]) + firstMin(i);
            else
                bound += secondMin(curr_path[level-1]) + firstMin(i);

            if (bound + cost[curr_path[level-1]][i] >= final_cost)
                continue; // prune

            // Make move
            curr_path[level] = i;
            visited[i] = true;

            TSP(curr_path, curr_cost + cost[curr_path[level-1]][i], level + 1);

            // Backtrack
            visited[i] = false;
            curr_path[level] = -1;
        }
    }
}

int main() {
    cout << "Enter number of cities: ";
    cin >> n;

    cout << "Enter " << n << "x" << n << " cost matrix (0 for same city, space separated):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
        }
    }

    int curr_path[11];
    for (int i = 0; i <= n; i++) {
        curr_path[i] = -1;
        visited[i] = false;
        final_path[i] = -1;
    }

    // Start from city 0
    curr_path[0] = 0;
    visited[0] = true;

    TSP(curr_path, 0, 1);

    // Output result
    cout << "\nMinimum cost: " << final_cost << endl;
    cout << "Path: ";
    for (int i = 0; i < n; i++) {
        cout << final_path[i];
        if (i < n-1) cout << " -> ";
    }
    cout << " -> 0" << endl;

    return 0;
}