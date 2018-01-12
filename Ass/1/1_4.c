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

int main() {
    long long int n, i, j;
    //scanf("%lld", &n); 

    return 0;
}