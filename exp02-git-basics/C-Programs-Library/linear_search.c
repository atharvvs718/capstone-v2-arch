/* Linear Search - finds the position of a key in an array */
#include <stdio.h>

int main(void) {
    int arr[] = {10, 23, 45, 70, 11, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    int key = 70, i, found = -1;

    for (i = 0; i < n; i++) {
        if (arr[i] == key) {
            found = i;
            break;
        }
    }

    if (found != -1)
        printf("Element %d found at index %d\n", key, found);
    else
        printf("Element %d not found\n", key);
    return 0;
}
