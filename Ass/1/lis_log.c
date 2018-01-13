#include <stdio.h>
#include <limits.h>

long long int counter = 0;
long long int a[1000000];
long long int substatus[1000000];
long long int a_nlogn[1000000];

long long int lis(long long int l, long long int r) {
    long long int i, j, k, n, max = 0, mloc = 0; 
    long long int b_l = l, b_r, b_m, set;
    /*for(i = l; i <= r; i++) { // iteration through the array
        k = 1;
        for(j = i-1; j >= l; j--) { // checks for LIS number
            if(a[j] < a[i] && substatus[j]+1 > k) {
                k = substatus[j]+1;
            }
        }
        //k++; only if k = 0 initially, as i originally did it
        substatus[i] = k;
        //printf("%lld ", k);
        if(k >= max) {
            max = k;
            mloc = i;
        }
    }*/
    for (i = l; i <= r; ++i)
    {
        a_nlogn[i] = LLONG_MIN;

        //substatus[i] = 0;
    }


    k = l;
    n = 0;
    for(i = l; i <= r; i++) {
        if(a_nlogn[l]==LLONG_MIN) {
            a_nlogn[l] = a[i];
            n = 1;
        }

        b_r = k;
        if(a[i] > a_nlogn[k]) {
            a_nlogn[++k] = a[i];
            n++;
        }
        else {
            b_m = (b_r-b_l)/2 + b_l;
            //binary search
            while(b_r > b_l) {
                b_m = (b_r-b_l)/2 + b_l;
 
                if(a_nlogn[b_m] > a[i]) {
                    b_r = b_m - 1;
                    set = b_m;
                }
                else if(a_nlogn[b_m] < a[i]) {
                    b_l = b_m + 1;
                    set = b_m + 1;
                }
                else {
                    break;//?
                }

            }
            if(a[i] < a_nlogn[l]) {
                a_nlogn[l] = a[i];
            }
            else if(a[i] < a_nlogn[set]) {
                a_nlogn[set] = a[i];
            }
            //a_nlogn[b_m] = a[i];

            
        }
        printf("Array after checking a[%lld] = %lld :\n", i, a[i]);
        for(j = l; j <= k; j++) {
            printf("%lld ", a_nlogn[j]);
        }
        printf("\n");
    }
/*
    for (i = l; i <= r; ++i)
    {
        a_nlogn[i] = 0;

        //substatus[i] = 0;
    }
*/
    return n;
}


int main(void) {
    long long int i, j, k, n, max = 0, mloc = 0; 
    scanf("%lld", &n); // number of inputs
    
    for(i = 0; i < n; i++) {
        scanf("%lld", &a[i]); // input into the array
    }
    printf("LIS length: %lld\n", lis(0, n-1));    

}