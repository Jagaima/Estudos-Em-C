#include <stdio.h>

int main() {
    int n, i, num, sum = 0;

    printf("Enter the number of integers to sum: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter number %d: ", i + 1);
        scanf("%d", &num);
        sum += num;
    }

    printf("The total sum is: %d\n", sum);

    return 0;
}