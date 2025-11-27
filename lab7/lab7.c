#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 20

// Function prototypes
void printOBST(int root[MAX][MAX], int i, int j, int keys[]);

int main() {
    int n, i, j, k, l, r;
    int keys[MAX];
    float p[MAX], q[MAX]; // p = successful search prob, q = unsuccessful
    float w[MAX][MAX], c[MAX][MAX];
    int root[MAX][MAX];

    printf("Enter number of keys: ");
    scanf("%d", &n);

    printf("Enter the keys (in sorted order):\n");
    for (i = 1; i <= n; i++)
        scanf("%d", &keys[i]);

    printf("Enter probabilities for successful searches (p1 to pn):\n");
    for (i = 1; i <= n; i++)
        scanf("%f", &p[i]);

    printf("Enter probabilities for unsuccessful searches (q0 to qn):\n");
    for (i = 0; i <= n; i++)
        scanf("%f", &q[i]);

    // Initialization
    for (i = 0; i <= n; i++) {
        w[i][i] = q[i];
        c[i][i] = 0;
    }

    // OBST DP computation
    for (l = 1; l <= n; l++) { // l = length of chain
        for (i = 0; i <= n - l; i++) {
            j = i + l;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            c[i][j] = INT_MAX;
            for (r = i + 1; r <= j; r++) {
                float t = c[i][r - 1] + c[r][j] + w[i][j];
                if (t < c[i][j]) {
                    c[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("\nOptimal Cost of OBST: %.3f\n", c[0][n]);
    printf("\nRoot Table (indices of roots):\n");
    for (i = 0; i <= n; i++) {
        for (j = 0; j <= n; j++) {
            if (i >= j)
                printf("  -  ");
            else
                printf("%3d  ", root[i][j]);
        }
        printf("\n");
    }

    printf("\nStructure of Optimal BST:\n");
    printOBST(root, 0, n, keys);

    return 0;
}

// Recursive function to print OBST structure
void printOBST(int root[MAX][MAX], int i, int j, int keys[]) {
    int r;

    if (i == j)
        return;

    r = root[i][j];

    printf("Root of subtree (%d, %d) is key: %d\n", i + 1, j, keys[r]);

    // Left subtree
    if (r - 1 != i) {
        printf("  Left child of %d is %d\n", keys[r], keys[root[i][r - 1]]);
        printOBST(root, i, r - 1, keys);
    } else {
        printf("  Left child of %d is NULL\n", keys[r]);
    }

    // Right subtree
    if (r != j) {
        if (r != j)
            if (r != j)
                if (r != j && r < j)
                    if (r != j)
                        if (r < j)
                            if (root[r][j] != 0)
                                printf("  Right child of %d is %d\n", keys[r], keys[root[r][j]]);
                            else
                                printf("  Right child of %d is NULL\n", keys[r]);
        printOBST(root, r, j, keys);
    }
}
