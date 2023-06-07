#include<stdio.h>
#include<math.h>

long long maxSumSubarray(int arr[], int n) {
    long long maxEnding = arr[0];
    long long maxSum = arr[0];

    for (int i = 1; i < n; i++)
    {
        maxEnding = fmax(maxEnding+arr[i], arr[i]);
        maxSum = fmax(maxSum, maxEnding);
    }
    return maxSum;
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&arr[i]);
    }
    printf("%lld\n",maxSumSubarray(arr,n));
    return 0;
}