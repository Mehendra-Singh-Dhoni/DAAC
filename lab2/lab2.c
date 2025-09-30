#include <stdio.h>

struct Item {
    int weight;
    int profit;
    float ratio;
};

void sortItems(struct Item items[], int n) {
    int i, j;
    struct Item temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (items[i].ratio < items[j].ratio) {
                temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }
}

void knapsackGreedy(struct Item items[], int n, int capacity) {
    int i, remaining = capacity;
    float totalProfit = 0.0;
    for (i = 0; i < n; i++) {
        if (items[i].weight <= remaining) {
            remaining -= items[i].weight;
            totalProfit += items[i].profit;
            printf("Item %d -> 100%% taken\n", i+1);
        } else {
            float fraction = (float) remaining / items[i].weight;
            totalProfit += items[i].profit * fraction;
            printf("Item %d -> %.2f%% taken\n", i+1, fraction * 100);
            break;
        }
    }
    printf("\nMaximum Profit = %.2f\n", totalProfit);
}

int main() {
    int n, capacity, i;
    printf("Enter number of items: ");
    scanf("%d", &n);
    struct Item items[n];
    for (i = 0; i < n; i++) {
        printf("Item %d profit: ", i+1);
        scanf("%d", &items[i].profit);
        printf("Item %d weight: ", i+1);
        scanf("%d", &items[i].weight);
        items[i].ratio = (float) items[i].profit / items[i].weight;
    }
    printf("Enter knapsack capacity: ");
    scanf("%d", &capacity);
    sortItems(items, n);
    knapsackGreedy(items, n, capacity);
    return 0;
}
