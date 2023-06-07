#include<stdio.h>

/*  Number of Comparisons:
    If n is odd: 3*(n-1)/2
    if n is even: 3n/2-2
*/

typedef struct Pair
{
    int min;
    int max;
} Pair;

Pair getMinMax(int arr[], int n) {
    Pair minmax;
    int i;

    if(n%2 == 0) {
        if(arr[0] <= arr[1]) {
            minmax.min = arr[0];
            minmax.max = arr[1];
        } else {
            minmax.min = arr[1];
            minmax.max = arr[0];
        }
        i = 2;
    } else {
        minmax.min = arr[0];
        minmax.max = arr[1];
        i = 1;
    }

    while (i < n-1)
    {
        if(arr[i] > arr[i+1]) {
            if(arr[i] > minmax.max)
                minmax.max = arr[i];
            if(arr[i+1] < minmax.min)
                minmax.min = arr[i+1];
        } else {
            if(arr[i+1] > minmax.max) 
                minmax.max = arr[i+1];

            if(arr[i] < minmax.min)
                minmax.min = arr[i];
        }
        i+=2;
    }
    return minmax;
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&arr[i]);
    }
    Pair res = getMinMax(arr, n);
    printf("Max: %d | Min: %d", res.max, res.min);
    return 0;
}