#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 10

int n;
int costMatrix[MAX][MAX];
int finalPath[MAX + 1];
int visited[MAX];
int finalRes = INT_MAX;

// Function to copy temporary solution to the final solution
void copyToFinal(int currPath[]) {
    for (int i = 0; i < n; i++)
        finalPath[i] = currPath[i];
    finalPath[n] = currPath[0];
}

// Find minimum edge cost having an end at vertex i
int firstMin(int i) {
    int min = INT_MAX;
    for (int k = 0; k < n; k++)
        if (costMatrix[i][k] != 0 && costMatrix[i][k] < min)
            min = costMatrix[i][k];
    return min;
}

// Find second minimum edge cost having an end at vertex i
int secondMin(int i) {
    int first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < n; j++) {
        if (i == j)
            continue;
        if (costMatrix[i][j] <= first) {
            second = first;
            first = costMatrix[i][j];
        } else if (costMatrix[i][j] <= second && costMatrix[i][j] != first)
            second = costMatrix[i][j];
    }
    return second;
}

// Recursive function for Branch and Bound
void TSPRec(int currBound, int currWeight, int level, int currPath[]) {
    if (level == n) {
        if (costMatrix[currPath[level - 1]][currPath[0]] != 0) {
            int currRes = currWeight + costMatrix[currPath[level - 1]][currPath[0]];
            if (currRes < finalRes) {
                copyToFinal(currPath);
                finalRes = currRes;
            }
        }
        return;
    }

    for (int i = 0; i < n; i++) {
        if (costMatrix[currPath[level - 1]][i] != 0 && !visited[i]) {
            int temp = currBound;
            currWeight += costMatrix[currPath[level - 1]][i];

            if (level == 1)
                currBound -= ((firstMin(currPath[level - 1]) + firstMin(i)) / 2);
            else
                currBound -= ((secondMin(currPath[level - 1]) + firstMin(i)) / 2);

            if (currBound + currWeight < finalRes) {
                currPath[level] = i;
                visited[i] = 1;
                TSPRec(currBound, currWeight, level + 1, currPath);
            }

            currWeight -= costMatrix[currPath[level - 1]][i];
            currBound = temp;

            for (int j = 0; j < n; j++)
                visited[j] = 0;
            for (int j = 0; j <= level - 1; j++)
                visited[currPath[j]] = 1;
        }
    }
}

// Main function
void TSP() {
    int currPath[MAX + 1];

    int currBound = 0;
    for (int i = 0; i < n; i++)
        currBound += (firstMin(i) + secondMin(i));
    currBound = (currBound & 1) ? currBound / 2 + 1 : currBound / 2;

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    visited[0] = 1;
    currPath[0] = 0;

    TSPRec(currBound, 0, 1, currPath);
}

int main() {
    printf("Enter number of cities: ");
    scanf("%d", &n);

    printf("Enter the cost matrix (%dx%d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &costMatrix[i][j]);

    TSP();

    printf("\nMinimum cost: %d", finalRes);
    printf("\nPath: ");
    for (int i = 0; i <= n; i++)
        printf("%d ", finalPath[i]);

    printf("\n");
    return 0;
}
