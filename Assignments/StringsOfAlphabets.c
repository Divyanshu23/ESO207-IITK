#include<stdio.h>

void generateStrings(int n, int k, char arr[], int start, char res[]) {
    if(start == n) {
        printf("%s\n", res);
        return;
    }

    for (int i = 0; i < k; i++)
    {
        res[start] = arr[i];
        generateStrings(n,k,arr,start+1,res);
    }   
}

int main() {
    int n, k;
    scanf("%d", &n);
    scanf("%d",&k);
    
    char arr[k];
    for (char i = 0; i < k; i++)
    {
        arr[i] = 'a'+i;
    }
    int start = 0;
    char res[n+1];
    res[n] = '\0';
    generateStrings(n,k, arr, start, res);
    return 0;
}