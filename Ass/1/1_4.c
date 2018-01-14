#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>

/*Note:
    --Input:
    n k
    a1 a2 a3 ... an
    --Output:
    -1 if sum(ai) < k
    0 if sum(ai) == k
    sequence if sum(ai) > k

    --Constraints:
    1 <= n <= 10^5
    0 <= k <= 10^14

    --------------------------
    Approach 1:
    // counts is a 0-indexed array that stores number of elements that
    // can be deleted i times, in the ith element 


    1. for each entry ai, counts[1->ai]++. Store max(ai)
    2. for i:1->max(ai)
    3.  sum+=counts[i]
    4.  if(sum > k) // check if > or >=
    5.      (CALC no used up, and no left)

    REALITY CHECK:
    count would normally require an array of 10^9.
    not possible.
    Solution: 
        1. loop through a naive map array to match. Complexity gets 
        worse with more elements
        issues: O(n^2), where n is 10^5
        2.implement a hash table?
        

    ---------------------------
    Approach 2:
    Much better
    Use binary search on an answer

*/


//Working with approach 1
/*long long int a[100007]; // stores ai
long long int count[100007]; // requires 10^9?
long long int track[100007]; // to map 

int main() {
    long long int n, i, j;
    //scanf("%lld", &n); 

    return 0;
}*/


long long int a[1000007];
long long int n, k;


//HELPER FUNCTION: PRINT ARRAY FROM L TO R
//
//
//
void printr(long long int l, long long int r) {
    if(l < 0 || r >= n) {
        return;
    }
    printf("\n------------------------------\n");
    long long int i;
    for(i = l; i <= r; i++) {
        printf("%lld ", a[i]);
    }
    printf("\n\n------------------------------\n\n");
}
//
//
//
//.......................................




//SORT SECTION
//
//
//


/*USAGE: 
    For use with long long int in C
    The functions must be initilaised before main(). The rest may come after. 
    Sorts by ascending order. 
    Call m_sort(array_name, start_index_of_array, end_index_of_array)
    Declare the array globally.
*/


void m_sort(long long int, long long int);
void merge(long long int, long long int);

/*
    Called first for merge purposes
    Recursively breaks the array into smaller arrays and passes them for merging
*/
void m_sort(long long int l, long long int r) {
    if(l==r)
        return;
    m_sort(l, ((l+r)/2));

    m_sort((((l+r)/2)+1), r);
    merge(l, r);
    return;
}

/*
    Called by function m_sort
    Merges the smaller arrays by comparing against each element in succession
*/
void merge(long long int l, long long int r) {
    long long int m = (l+r)/2 + 1;
    long long int start = 0;
    long long int b[r-l+1];
    long long int i, j;
    
    long long int cl = l, cr = r, cm = m;
    while(start <= r-l) {
        if(((a[cl] >= a[cm])||(cm>r)) && (cl<m)) {
            b[start++] = a[cl++];       }
        else {
            b[start++] = a[cm++];
        }
    }
    for(i = l, j = 0; i <= r; i++, j++) {
        a[i] = b[j];
    }
    return;
}
//
//
//
//-----------------------------------------





//TIME CALCULATOR FUNCTION:
//
//
//
long long int tme(long long int ub, long long int lb) { // it's inverted as that's array behaviour
    return (a[ub] - a[lb] + 1)*a[ub];
}
//
//
//
//-----------------------------------------



//
//
//
//
long long int sch(long long int lb, long long int ub) {
    long long int c = k, i = 0, j = 0, ans = 0, max = 0, t;
    // c keeps track of the box/container I am in. Should be 0 at the end. 
    // i, j are binding variables that loop through the array to point out which element(s) I am referring to
    // ans is the midpoint of the bounds of the search space. It stored probable answers, and eventually returns such
    // max is the answer for a given constraint. At the correct constraint, it is equal to ans at the end
    // t is a temp variable that stores the times

    ans = (ub - lb)/2 + lb; 
    //if(ans*2 < lb+ub) {
    //    ans = ans + 1; // rounding up for a rounding bug
    //} 

    printf("Searching within %lld to %lld at %lld\n", lb, ub, ans);


    while(j < n) {
        t = tme(i, j); // calculates and stores time

        printf("Time taken for %lld to %lld in array is %lld\n", i, j, t);

        if(t < ans) { // Scope for adding more to the current box

            printf("More addable\n");

            j = j + 1;
            if(j == n) {
                printf("We're at the end of the straw\n");
                c--; // box completed
            }
        }
        else if(t > ans) { // box is /overflowing

            printf("t was greater than ans. New box being created\n");

            c--;
            if(i == j) { // inaccessible? edge case
                i++;
                j++;
            }
            i = j;
            continue; // we do not want to consider the answer for t
        }
        else { // box just fit
            printf("t fit in ans. New box being created\n");

            c--;
            i = j+ 1;
            j = i;
        }

        if(t > max) {
            max = t;
        }

    }
    printf("-----------\nmax = %lld\nans = %lld\nc = %lld\n", max, ans, c);

    if(c < 0) { // too small a boundary
        printf("c < 0. Boundary is too small. Increasing lb to ans\n");
        if(ub-lb == 1) {
            return ub; // haxxx
        }
        return sch(ans, ub);
    }
    if(ans-max > 0) { // too big a boundary
        printf("ans-max > 0. Boundary is too big. Decreasing ub to ans\n"); 
        if(ub-lb == 1) {
            return lb; // haxxx
        }
        return sch(lb, ans);
    }
    if(ans - max == 0 && c == 0) { // perfect
        printf("Got the answer:\n");
        return ans;
    }

}
//
//
//
//-----------------------------------------



int main() {
    long long int i, j, ans;
    scanf("%lld %lld", &n, &k);

    for(i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    } 

    m_sort(0, n-1); // sort in reverse order
    printr(0, n-1); //sort works fine

    ans = sch(tme(0, 0), tme(0, n-1)); // passes to the search function the lower and upper time bound limits.
    printf("%lld\n", ans);
    return 0;
}
