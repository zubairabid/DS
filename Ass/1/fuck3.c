#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>


long long int m_sort(long long int, long long int);
long long int merge(long long int, long long int);

long long int a[1000009];


int main() {
    long long int n, i, j;
    scanf("%lld", &n); //  length of the array

    for(i = 0; i < n; i++) { // input to array asked for
        scanf("%lld", &a[i]);
    }

    long long int result = m_sort(0, n-1);

    printf("%lld\n", result);
    
    for(i = 0; i < n; i++) { //prints the array
        printf("%lld ", a[i]);
    }
    printf("\n");
    
    return 0;
}


/*
	Called first for merge purposes
	Recursively breaks the array into smaller arrays and passes them for merging
*/
long long int m_sort(long long int l, long long int r) {
    long long int counter = 0;
    if(l==r)
        return counter;
    counter += m_sort(l, ((l+r)/2));

    counter += m_sort((((l+r)/2)+1), r);
    counter += merge(l, r);
    return counter;
}

/*
	Called by function m_sort
	Merges the smaller arrays by comparing against each element in succession
*/
long long int merge(long long int l, long long int r) {
    long long int m = (l+r)/2 + 1;
    long long int start = 0;
    long long int b[r-l+1];
	long long int i, j, counter = 0;
	long long int temp = -832974329;

    long long int cl = l, cr = r, cm = m;
    while(start <= r-l) {
        if(cl < m && ((a[cl] <= a[cm])||((cm>r) && (cl<m)))) { // ISSUE: fails for exact fitting arrays?
            b[start++] = a[cl++];       
        }
        else {
            /*if(start < m-l) { // if right goes to left
                counter++;
            }*/
            if(cl < m && temp != a[cl]) {
                temp = cl;
                counter++;
            }
            b[start++] = a[cm++];
        }
    }
    for(i = l, j = 0; i <= r; i++, j++) {
        a[i] = b[j];
    }
    return counter;
}