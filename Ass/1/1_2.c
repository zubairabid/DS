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
    long long int i, j, k, n, T = 0;
    long long int lb = 0, ub = 1000000000000, tim, ans;

    scanf("%lld %lld", &n, &k);
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
        a[i] = vel[i]; // for calculating if it's possible at all
    } // sorting the array
    
    m_sort(0, n-1);
    if(invers < k) { // not possible
        printf("-1\n");
    }
    // else if(k == 0) {
    //     printf("0\n");
    // }
    else { // possible
        // printf("Binary searching for the answer.\n");
        //invers = -1;
        /*while(invers != k) {
            invers = 0;
            tim = lb + (ub-lb) / 2;
            // printf("Looking at time: %lld\nNew distances:\n", tim);
            for (i = 0; i < n; ++i)
            {
                a[i] = dis[i] + tim * vel[i];
                // printf("%lld ", a[i]);
            }
            // printf("\n");
            m_sort(0, n-1);
            // printf("Number of inversions: %lld\n", invers);
            if(invers < k) {
                if(lb >= ub || ub < tim || lb > tim) {
                    break;
                }
                // printf("invers < k, increasing lb from %lld to %lld \n", lb, tim+1);
                lb = tim+1;
            }
            else if (invers > k) {
                ans = tim;
                if(lb >= ub || ub < tim || lb > tim) {
                    break;
                }
                // printf("invers < k, decreasing ub from %lld to %lld \n", ub, tim-1);
                ub = tim-1;
            }
            else {
                ans = tim;
                if(lb >= ub || ub < tim || lb > tim) {
                    break;
                }
                // printf("%lld matches k inversions, decreasing ub from %lld to %lld to check for more\n", tim, ub, tim-1);
                ub = tim - 1;
                invers = 0;
            }
        }*/

        while(lb < ub) {
            invers = 0;
            tim = (lb+ub)/2;

            for (i = 0; i < n; ++i)
            {
                a[i] = dis[i] + tim * vel[i];
                // printf("%lld ", a[i]);
            }
            m_sort(0, n-1);
            // printf("Number of inversions: %lld\n", invers);
            if(invers < k) {
                lb = tim + 1;
            }
            else {
                
                ub = tim;
            }
        }

        printf("%lld\n", lb);
    }
    



    
    /*for (i = 0; i < n; ++i)
    {
        printf("%lld ", dis[i]);
    }
    printf("\n");  

    for (i = 0; i < n; ++i)
    {
        printf("%lld ", vel[i]);
    }
    printf("\n");  
    */

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
    long long int b[r-l+1]; // to swap a
    long long int c[r-l+1]; // to swap vel
    long long int i, j;
    long long int inv = 0; // to calculate number of inversions per merge.
    // long long int badstuff = 0;

    long long int cl = l, cr = r, cm = m;
    while(start <= r-l) {
        // printf("Bounds: l = %lld, m = %lld, r = %lld\n", l, m, r);
        // printf("cl = %lld, cm = %lld, a[cl] = %lld, vel[cl] = %lld, a[cm] = %lld, vel[cm] = %lld\n", cl, cm, a[cl], vel[cl], a[cm], vel[cm]);

        if(((a[cl] <= a[cm])||(cm>r)) && (cl<m)) {
            if(normiesort == 1) {
                if(a[cl] == a[cm] && cm <= r) {
                    // printf("a[cl] == a[cm].\n");
                    if(vel[cl] <= vel[cm]) {
                        // printf("vel[cl] = %lld < vel[cm] = %lld\n",vel[cl], vel[cm]);
                        // printf("Adding a[cl] = %lld, vel[cl] = %lld\n", a[cl], vel[cl]);
                        c[start] = vel[cl]; 
                        b[start++] = a[cl++];
                    }
                    else {
                        // printf("vel[cl] = %lld > vel[cm] = %lld\n",vel[cl], vel[cm]);
                        // printf("Adding a[cm] = %lld, vel[cm] = %lld\n", a[cm], vel[cm]);
                        c[start] = vel[cm];
                        b[start++] = a[cm++];
                        // badstuff = badstuff == 0? 1: 0;
                    }
                    continue;
                }
                else {
                    // printf("Adding vel[cl] = %lld\n", vel[cl]);
                    c[start] = vel[cl];
                }
            }


            // printf("Adding a[cl] = %lld\n", a[cl]);
            b[start++] = a[cl++];       
        }
        else {
            if(normiesort == 1) {
                // printf("Adding vel[cm] = %lld\n", vel[cm]);
                c[start] = vel[cm];
            }
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
        if(normiesort == 1) {
            vel[i] = c[j];
        }
    }
    return inv;
}
