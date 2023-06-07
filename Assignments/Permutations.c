#include<stdio.h>

void swap(char* a, char* b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void permutations(char str[], int n, int s) {
    if(s == n-1) {
        printf("%s\n", str);
        return;
    }

    int count[26] = {0};
    for (int i = s; i < n; i++)
    {
        if(count[str[i]-'a'] == 0) {
            count[str[i]-'a']++;
            swap(&str[s], &str[i]);
            permutations(str, n, s+1);
            swap(&str[s], &str[i]);
        }
    }
}


int main() {
    int n;
    scanf("%d", &n);
    char str[n+1];
    scanf("%s",str);
    permutations(str, n, 0);
    return 0;
}