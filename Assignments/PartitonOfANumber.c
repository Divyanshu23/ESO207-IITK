#include<stdio.h>

void partition(int n, char res[], int s, int t) {
    if(n == 0) {
        res[s] = '\0';
        printf("%s\n",res);
        return;
    }

    for (int i = t; i <= n; i++)
    {
        res[s] = i + '0';
        partition(n-i,res, s+1, i);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    char res[n+1];
    res[n] = '\0';
    partition(n,res, 0, 1);
    return 0;
}