#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int** buildSparseTable(int arr[], int n) {
    int k = log2(n);
    int** table = (int**)malloc(n*sizeof(int*));

    for (int i = 0; i < n; i++) {
        table[i] = (int*)malloc(k*sizeof(int));
        table[i][0] = arr[i];
    }

    for (int j = 1; j < k; j++) {
        for (int i = 0; i + (1<<j) <= n; i++) {
            table[i][j] = fmin(table[i][j-1], table[i + (1 << (j-1))][j-1]);
        }
    }
    return table;
}

int rangeMinimaQuery(int** table, int l, int h) {
    int len = h - l + 1;
    int k = log2(len);
    return fmin(table[l][k], table[h-(1<<k)+1][k]);
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d",&arr[i]);
    }

    int k = log2(n);
    int** table = buildSparseTable(arr, n);
    int l, h;
    scanf("%d %d", &l,&h);
    printf("%d\n", rangeMinimaQuery(table, l, h));
    return 0;
}