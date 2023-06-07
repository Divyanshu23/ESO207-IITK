#define mod 2021

#include<stdio.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<limits.h>

int RFib(long long n) {
    if(n == 0 || n == 1) return n;
    else return (RFib(n-1) + RFib(n-2))%mod;
}

int IFib(long long n) {
    if(n == 0 || n == 1) return n;

    long long a = 0;
    long long b = 1;
    int ans;

    for (long long i = 2; i <= n; i++)
    {
        ans = (a+b)%mod;
        a = b;
        b = ans;
    }
    return ans;
}

void ComputePow(int arr[2][2], long long n) {
    if(n == 0 || n == 1) return;

    int arrCopy[2][2];
    memcpy(arrCopy, arr, sizeof(arrCopy));
    ComputePow(arr,n/2);

    int arrPowCopy[2][2];
    memcpy(arrPowCopy, arr, sizeof(arrPowCopy));

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            arr[i][j] = 0;
            for (int k = 0; k < 2; k++)
            {
                arr[i][j] += (arrPowCopy[i][k]*arrPowCopy[k][j])%mod;
            }
            arr[i][j] = arr[i][j]%mod;
        }
        
    }

    if(n % 2 != 0) {
        memcpy(arrPowCopy, arr, sizeof(arrPowCopy));

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                arr[i][j] = 0;
                for (int k = 0; k < 2; k++)
                {
                    arr[i][j] += (arrPowCopy[i][k]*arrCopy[k][j])%mod;
                }
                arr[i][j] = arr[i][j]%mod;
            }
        }
    }
    return;
}

int CleverFib(long long n) {
    if(n == 0 || n == 1) return n;

    int arr[2][2] = {{1,1}, {1,0}};
    ComputePow(arr,n-1);
    return arr[0][0];
}

int main() {
    long long n;
    printf("Enter n: ");
    scanf("%lld", &n);

    clock_t start_t, end_t;
    double total_t;
    int ans;

    start_t = clock();
    ans = CleverFib(n);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("CleverFib(%lld): %d | Running Time: %lf\n",n, ans, total_t);

    start_t = clock();
    ans = IFib(n);
    end_t = clock();   
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("IFib(%lld): %d | Running Time: %lf\n",n, ans, total_t);

    start_t = clock();
    ans = RFib(n);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("RFib(%lld): %d | Running Time: %lf\n",n, ans, total_t);
    
    return 0;
}