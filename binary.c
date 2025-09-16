#include <stdio.h>

// Binary Search function
int binarySearch(int arr[], int size, int key) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == key) return mid;   // element found
        else if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;  // element not found
}

int main() {
    int arr[50], n, key, result;

    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter elements in sorted order:\n");
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    printf("Enter element to search: ");
    scanf("%d", &key);

    result = binarySearch(arr, n, key);
    if (result != -1)
        printf("Element %d found at index %d.\n", key, result);
    else
        printf("Element not found.\n");

    return 0;
}
