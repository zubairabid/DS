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

/*Note:
    Given the constraints in the problem, merge sort will need to be modified a bit
    Any displacement creates issues
    Eg: 1 2 6 8 3 4 5 7 : 2 displacements, [2]-->[5] (1 2 8 3 4 5 6 7), [3]-->[7] (1 2 3 4 5 6 7 8)
        Alternate way: (1 2 6 8 3 4 5 7) --> 

        1 2 6 8     3 4 5 7
        _ _ _ _ _ _ _ _

        1 _ _ _ _ _ _ _                                 [left preference begins]
        1 2 _ _ _ _ _ _
        1 2 3 _ _ _ _ _ (3[4] -> 3[2]; 6[2] -- )        ++
        1 2 3 4 _ _ _ _ (4[5] -> 4[3]; 8[3] -- ) <6>    ++
        1 2 3 4 5 _ _ _                                 [right preference begins]
        1 2 3 4 5 6 _ _ (<6> -> 6[5]; 7 -> <7> )        --/++
        1 2 3 4 5 6 7 _ (<7> -> 7[6]; )                 --
        1 2 3 4 5 6 7 8 (<8> -> 8[7]; )                 --




        5 6 7 8     1 2 3 4
        ans: 4

        Now: each half is sorted, which implies that there is only a displacement if something moves to another half
        Update: (11.01.2018) :  I increment the counter if something from the right half moves to the left half. Works
                                for the test cases supplied in the question, but not for OJ (WA). Some bug which needs 
                                to be fixed, it seems. 

    



*/

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

