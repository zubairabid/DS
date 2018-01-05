#include <stdio.h>
long long int a[1000007], len;
long long int temp;

void swap(long long int c, long long int b) {
	temp = a[b];
	a[b] = a[c];
	a[c] = temp;
}

void sort(long long int lef, long long int rig) {
	if(rig - lef == 1) {
		return; // if the length of the array is 1, it has been sorted
	}
	l = lef; // backups
	r = rig;
	long long int pivot;
	pivot = (l + r)/2;

	while(r > l) { // swapperooo
		while(a[l] <= a[pivot]) { // keeping everything left
			l++;
			if(l == len) { // edge
				swap(len-1, pivot);
				break;
			}
		}
		while(a[r] > a[pivot]) { // keeping everything right
			r--;
			if(r == -1) { // edge
				swap(0, pivot);
				break;
			}
		}
		if(r <= l) {
			swap(l, r); //huh please work
		}
		swap(l, pivot);//please
	}

	sort(lef, pivot-1); // recursion
	sort(pivot+1, rig);

	return;
}

int main() {
/*

sort: lef, rig
	if(rig-lef == 1)
		return;
	l = lef + 1;
	r = rig;
	set pivot = (l+r)/2

	split//while(r < l):
		while(a[l] <= a[pivot]):
			l++;
			if(l == len):
				swap to end
				break off
		while(a[r] >= a[pivot]):
			r--;
			if(r == -1):
				swap to beginning
				break off
		if(r <= l):
			swap(a[l], a[r]);
		swap(a[l], a[pivot]);
	sort(l, pivot-1);
	sort(pivot+1, r);

*/
	long long int l, i, r;
	scanf("%lld", &len);
	for(i = 0; i < len; i++) {
		scanf("%lld", &a[i]);
	}	
	l = 0;
	r = len - 1;
	sort(l, r);
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