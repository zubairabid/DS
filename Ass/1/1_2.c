#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>

/*USAGE: 
    For use with long long int in C
    The functions must be initilaised before main(). The rest may come after. 
    Sorts by ascending order. 
    Call m_sort(array_name, start_index_of_array, end_index_of_array)
    Declare the array globally.
*/
long long int a[100007];
long long int dis[100007]; // dist array
long long int vel[100007]; // velocity
long long int invers = 0;
long long int normiesort = 1; // when 1, checks the == thing. 

void m_sort(long long int, long long int);
long long int merge(long long int, long long int);

int main() {
    long long int i, j, k, n, T;

    scanf("%lld", &n);
    for (i = 0; i < n; ++i) {
        scanf("%lld", &a[i]);
        //a[i] = mar[i];
    }
    for (i = 0; i < n; ++i) {
        scanf("%lld", &vel[i]);
        //a[i] = mar[i];
    }

    m_sort(0, n-1);
    normiesort = 0;
    for (i = 0; i < n; ++i) {
        dis[i] = a[i];
    } // sorting the array

    for (i = 0; i < n; ++i)
    {
        printf("%lld ", dis[i]);
    }
    printf("\n");  

    for (i = 0; i < n; ++i)
    {
        printf("%lld ", vel[i]);
    }
    printf("\n");  

    return 0;
}

/*
    Called first for merge purposes
    Recursively breaks the array into smaller arrays and passes them for merging
*/
void m_sort(long long int l, long long int r) {
    if(l==r)
        return;
    // printf("Splitting array into %lld->%lld\n", l, (l+r)/2);
    m_sort(l, ((l+r)/2));

    // printf("Splitting array into %lld->%lld\n", ((l+r)/2)+1, r);
    m_sort((((l+r)/2)+1), r);

    // printf("Merging from %lld to %lld\n", l, r);
    invers += merge(l, r);
    return;
}

/*
    Called by function m_sort
    Merges the smaller arrays by comparing against each element in succession
*/
long long int merge(long long int l, long long int r) {
    long long int m = (l+r)/2 + 1;
    long long int start = 0;
    long long int b[r-l+1];
    long long int i, j;
    long long int inv = 0; // to calculate number of inversions per merge.
    
    long long int cl = l, cr = r, cm = m;
    while(start <= r-l) {
        // printf("cl = %lld, cm = %lld, a[cl] = %lld, a[cm] = %lld\n", cl, cm, a[cl], a[cm]);

        if(((a[cl] <= a[cm])||(cm>r)) && (cl<m)) {
            if(normiesort == 1) {
                if(a[cl] == a[cm]) {
                    if(vel[cl] <= vel[cm]) {
                        b[start++] = a[cl++];
                    }
                    else {
                        b[start++] = a[cm++];
                    }
                    continue;
                }
            }


            // printf("Adding a[cl] = %lld\n", a[cl]);
            b[start++] = a[cl++];       }
        else {
            // printf("Adding a[cm] = %lld\n", a[cm]);
            if(a[cl] > a[cm]) {
                // printf("%lld > %lld, inversion addition to %lld\n", a[cl], a[cm], (m-cl));
                inv += m - cl;
            }
            b[start++] = a[cm++];
        }
    }
    for(i = l, j = 0; i <= r; i++, j++) {
        a[i] = b[j];
    }
    return inv;
}
