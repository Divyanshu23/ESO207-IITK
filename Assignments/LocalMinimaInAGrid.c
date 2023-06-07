#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

int findMinimumInRow(int* arr[], int l, int h, int r) {
    int curr = l;

    for (int i = l+1; i <= h; i++)
    {
        if(arr[r][i] < arr[r][curr])
            curr = i;
    }
    return curr;
}

int findMinimumInColumn(int* arr[], int l, int h, int c) {
    int curr = l;

    for (int i = l+1; i <= h; i++)
    {
        if(arr[i][c] < arr[curr][c])
            curr = i;
    }
    return curr;
}

int localMinima(int* arr[], int n) {
    int rL = 0, rH = n -1;
    int cL = 0, cH = n-1;
    int indx, cMid, rMid;
    bool colFlag = true;

    while ((rL <= rH) && (cL <= cH))
    {
        if(colFlag) {
            colFlag = false;
            cMid = cL + (cH - cL)/2;
            indx = findMinimumInColumn(arr, rL, rH, cMid);
            if(cL == cH) break;
            else if(cL == cH-1) {
                if(arr[indx][cMid] <= arr[indx][cMid+1]) break;
                else cL = cMid+1;
            } else {
                if(arr[indx][cMid] <= arr[indx][cMid-1] && arr[indx][cMid] <= arr[indx][cMid+1]) break;
                else if(arr[indx][cMid] > arr[indx][cMid-1]) cH = cMid-1;
                else cL = cMid+1;
            }
        } else {
            colFlag = true;
            rMid = rL + (rH - rL)/2;
            indx = findMinimumInRow(arr, cL, cH, rMid);
            if(rL == rH) break;
            else if(rL == rH-1) {
                if(arr[rMid][indx] <= arr[rMid+1][indx]) break;
                else rL = rMid+1;
            } else {
                if(arr[rMid][indx] <= arr[rMid-1][indx] && arr[rMid][indx] <= arr[rMid+1][indx]) break;
                else if(arr[rMid][indx] > arr[rMid-1][indx]) rH = rMid-1;
                else rL = rMid+1;
            }
        }
    }
    if(!colFlag) return arr[indx][cMid];
    else return arr[rMid][indx];
}

int main() {
    int n;
    scanf("%d", &n);
    int* arr[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = (int*)malloc(n*sizeof(int));
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }
    printf("Local Minima: %d\n", localMinima(arr, n));
    return 0;
}