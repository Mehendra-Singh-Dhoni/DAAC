#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 20

// Function prototypes
void buildTree(int root[MAX][MAX], int i, int j, int parent, int isLeft, int keys[], int *tree, int n);
void printTree(int *tree, int index, int level, int n);

int main() {
    int n, i, j, r, l;
    int keys[MAX];
    float p[MAX], q[MAX];
    float w[MAX][MAX], c[MAX][MAX];
    int root[MAX][MAX];

    printf("Enter number of keys: ");
    scanf("%d", &n);

    printf("Enter keys (sorted):\n");
    for (i = 1; i <= n; i++)
        scanf("%d", &keys[i]);

    printf("Enter probabilities for successful searches (p1 to pn):\n");
    for (i = 1; i <= n; i++)
        scanf("%f", &p[i]);

    printf("Enter probabilities for unsuccessful searches (q0 to qn):\n");
    for (i = 0; i <= n; i++)
        scanf("%f", &q[i]);

    // Initialize w and c tables
    for (i = 0; i <= n; i++) {
        w[i][i] = q[i];
        c[i][i] = 0;
    }

    // OBST dynamic programming
    for (l = 1; l <= n; l++) {
        for (i = 0; i <= n - l; i++) {
            j = i + l;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            c[i][j] = INT_MAX;
            for (r = i + 1; r <= j; r++) {
                float cost = c[i][r - 1] + c[r][j] + w[i][j];
                if (cost < c[i][j]) {
                    c[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("\nOptimal Cost of OBST: %.3f\n", c[0][n]);
    printf("\nRoot Table (indices):\n");
    for (i = 0; i <= n; i++) {
        for (j = 0; j <= n; j++) {
            if (i >= j)
                printf("  -  ");
            else
                printf("%3d  ", root[i][j]);
        }
        printf("\n");
    }

    // Build tree representation
    int tree[MAX];  // parent-child relationship by index
    for (i = 0; i < MAX; i++)
        tree[i] = -1;

    int mainRoot = root[0][n];
    tree[mainRoot] = 0; // 0 = root (no parent)

    buildTree(root, 0, n, mainRoot, 0, keys, tree, n);

    printf("\n\nOptimal Binary Search Tree (sideways view):\n\n");
    printTree(tree, mainRoot, 0, n);

    return 0;
}

// Recursive function to link left/right children
void buildTree(int root[MAX][MAX], int i, int j, int parent, int isLeft, int keys[], int *tree, int n) {
    int r = root[i][j];
    if (r == 0)
        return;

    // Left child
    if (r - 1 >= i + 1 && root[i][r - 1] != 0) {
        int left = root[i][r - 1];
        tree[left] = r;
        buildTree(root, i, r - 1, left, 1, keys, tree, n);
    }

    // Right child
    if (r < j && root[r][j] != 0) {
        int right = root[r][j];
        tree[right] = r;
        buildTree(root, r, j, right, 0, keys, tree, n);
    }
}

// Recursive print of tree (sideways)
void printTree(int *tree, int index, int level, int n) {
    if (index == 0 || index > n)
        return;

    // Right child first (prints on top)
    int right = -1, left = -1;
    for (int i = 1; i <= n; i++) {
        if (tree[i] == index && i > index)
            right = i;
        if (tree[i] == index && i < index)
            left = i;
    }

    printTree(tree, right, level + 1, n);

    for (int i = 0; i < level; i++)
        printf("        ");  // indentation
    printf("%d\n", index); // print current node index (key position)

    printTree(tree, left, level + 1, n);
}
