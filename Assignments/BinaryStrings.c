#include<stdio.h>

void generateBinaryStringsNonConsecutive1s(int n, int len, char res[]) {
    if(len == n) {
        printf("%s\n", res);
        return;
    }

    for (int i = 0; i < 2; i++)
    {
        if(len == 0) {
            res[len] = (0+i)+'0';
        } else if(res[len-1] == '0') {
            res[len] = (0+i)+'0';
        } else if(res[len-1] == '1') {
            res[len] = '0';
            generateBinaryStringsNonConsecutive1s(n,len+1,res);
            break;
        }
        generateBinaryStringsNonConsecutive1s(n,len+1,res);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int len = 0;
    char res[n+1];
    res[n] = '\0';
    generateBinaryStringsNonConsecutive1s(n, len, res);
    return 0;
}