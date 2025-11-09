#include <stdio.h>
#include <stdlib.h>

struct Item {
    int value;
    int weight;
    double ratio;
};

void selectionsort(struct Item items[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (items[j].ratio > items[i].ratio) {
                struct Item temp = items[j];
                items[j] = items[i];
                items[i] = temp;
            }
        }
    }
}

double fractionalKnapsack(int val[], int wt[], int n, int capacity) {
    struct Item items[n];
    
    // Step 1: Fill items array
    for (int i = 0; i < n; i++) {
        items[i].value = val[i];
        items[i].weight = wt[i];
        items[i].ratio = (double) val[i] / wt[i];
    }

    // Step 2: Sort by ratio (descending)
    selectionsort(items, n);

    double totalvalue = 0.0;
    int remaining = capacity;

    printf("\nItems selected:\n");
    printf("Value\tWeight\tRatio\t\tTaken\n");
    printf("----------------------------------------\n");

    // Step 3: Take items greedily
    for (int i = 0; i < n && remaining > 0; i++) {
        if (items[i].weight <= remaining) {
            // Take the full item
            totalvalue += items[i].value;
            remaining -= items[i].weight;
            printf("%d\t%d\t%.2f\t\tFull\n", items[i].value, items[i].weight, items[i].ratio);
        } else {
            // Take fractional part
            double fraction = (double) remaining / items[i].weight;
            totalvalue += items[i].value * fraction;
            printf("%d\t%d\t%.2f\t\t%.2f part\n", items[i].value, items[i].weight, items[i].ratio, fraction);
            remaining = 0;
            break;
        }
    }

    printf("----------------------------------------\n");
    printf("Total value in knapsack = %.2f\n", totalvalue);
    return totalvalue;
}

int main(void) {
    int n = 3, capacity = 50;
    int val[] = {60, 100, 120};
    int wt[]  = {10, 20, 30};

    double ans = fractionalKnapsack(val, wt, n, capacity);
    printf("\nExpected output: 240.00\n");
    return 0;
}
