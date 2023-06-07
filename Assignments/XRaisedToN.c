#include<stdio.h>
#define mod 2021

int raise(int x, long long n) {
    int res = 1;
    while (n) {
        if(n & 1) {
            res = (res*x)%mod;
        }
        x = x*x;
        n = n>>1;
    }
    return res;
}

int main() {
    int x;
    long long n;
    scanf("%d",&x);
    scanf("%lld", &n);
    printf("x raised to n: %d", raise(x,n));
    return 0;
}