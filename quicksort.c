#include <stdio.h>

int main() {
	// var block
	long long int lar_l = 1;
	long long int smo_r = -1; // to change once length set
	long long int len, i, j, pivot = 0, temp;
	long long int ar[10007];

	// input block
	scanf("%lld", &len); // the length of the array
	for(i = 0; i < len; i++) {
		scanf("%lld", &ar[i]); // each element of the array
	}

	// misc
	smo_r = len - 1;

	while(lar_l < smo_r) { // TODO insert condition later
		if(ar[lar_l] < ar[pivot]) {
			// fine
			lar_l++;
		}
		if(ar[smo_r] > ar[pivot]) {
			// fine
			smo_r--;
		}
		
	}
	if(lar_l > smo_r) {
		// swap
		temp = ar[lar_l];
		ar[lar_l] = ar[smo_r];
		ar[smo_r] = temp;
	}


	return 0;
}

/*
pivot: a[0] = 4
4 7 3 1 2 8 6 9 (lar_l: 1; smo_r: 4; swap a[1],a[4]; swap a[pivot],a[smo_r - 1])
- 4 2 3 1 7 8 6 9
pivot: a[2] = 3
1 2 3 4 7 8 6 9
pivot: a[5] = 8
1 2 3 4 7 8 6 9
-

1 2 3 4 7 8 6 9 // don't use the first. bug.

------ideal-------
1 2 9 3 4 5 6 7 8 (; swap at 0, 0)
/
1 2 9 3 4 5 6 7 8 (; swap at 1, 1)
/
1 2 9 3 4 5 6 7 8 (swap at 3, 8; swap at 2, 8)
1 2 3 8 4 5 6 7 9 (; swap at 2, 2)
1 2 3 8 4 5 6 7 9 (swap at 4, 7; swap at 3, 7)
1 2 3 4 7 5 6 8 9 (swap at 3, 3)
1 2 3 4 7 5 6 8 9 (swap at 5, 6; swap at 4, 6)
1 2 3 4 5 6 7 8 9
-------------------
4 7 9 6 1 2 3 8 (swap at 1, 6; )
4 3 9 6 1 2 7 8 (swap at 2, 5; )
4 3 2 6 1 9 7 8 (swap at 3, 4; )
4 3 2 1 6 9 7 8 r/l mismatch, swap pivot, r
1 3 2 4 6 9 7 8 (r/l mismatch, swap pivot, r at 0, 0)
1 3 2 4 6 9 7 8 (r/l mismatch, swap 2, 2; swap pivot, r at 1, 2)
1 2 3 4 6 9 7 8//
1 2 3 4 6 9 7 8
.
.
.
.






4 7 9 6 1 2 3 8 
- 4 3 9 6 1 2 7 8 (swap at l=1, r=6)
- 4 3 2 6 1 9 7 8 (swap at l=2, r=5)
- 4 3 2 1 6 9 7 8 (swap at l=3, r=4)
(l=4, r=3)
(swap pivot and r)
- 1 3 2 4 6 9 7 8
1 3 2 4 6 9 7 8
-

 */