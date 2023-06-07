#include<stdio.h>

int localMinima(int arr[], int n) {
    int low = 0, high = n-1;
    int mid;

    while (low <= high)
    {
        mid = low + (high - low)/2;
        if(low == high) break;
        else if(low == high-1) {
            if(arr[mid] <= arr[mid+1]) break;
            else {
                low = mid+1;
            }
        } else {
            if(arr[mid] <= arr[mid+1] && arr[mid] <= arr[mid-1]) break;
            else if(arr[mid+1] < arr[mid]) low = mid+1;
            else high = mid-1;
        }
    }
    return arr[mid];
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&arr[i]);
    }
    printf("%d", localMinima(arr,n)); 
    return 0;
}