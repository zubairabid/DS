#include <stdio.h>

long long int n, k;
long long int a[1000007];

void cl(long long int cn, long long int ck) {
	long long int point = 0, i, c= 0;
	long long int rs = ck/cn;


	//printf("In function cl. cn = %lld, ck = %lld, rs = %lld. new ck = %lld\n",cn, ck, rs, (ck - rs * cn));

	ck = ck - rs * cn;


	if(rs != 0) {
		for (i = 0; i < n; ++i)
		{
			if(a[i] != 0) {
				a[i] = a[i] - rs;
				if(a[i] < 0) {
					ck = ck - a[i];
	//				printf("a[%lld] = 0 now. ck+=%lld, ck = %lld. cn= %lld\n", i, (a[i]), ck, cn);
					a[i] = 0;
				}
				if(a[i] == 0) {
					cn--;
	//				printf("Since a[i] = 0, cn = %lld\n", cn);
				}
			}
		}
		cl(cn, ck);
	}
	else {
	//	printf("Initiating manual removal + print\n");

		for(i = 1; i <= ck;) {
			if(a[point%n] == 0) {
				point++;
			}
			else {
				a[point%n] -= 1;
				
	//			printf("a[%lld]-=1, now = %lld. i++, i = %lld\n", (point%n), a[point%n], (i+1));

				if(a[point%n] == 0) {
					cn--;
				}
				i++;
				point++;
			}
		}
	//	printf("Printing\n");
		for(0i = point, c = 1; c<=cn; i++) {
			if(a[i%n] == 0) {
				continue;
			}
			else {
				printf("%lld ", (((i+1)%n)==0?n:((i+1)%n)));
				c++;
			}
		}
		printf("\n");
	}
}


int main() {
	long long int i;
	scanf("%lld %lld", &n, &k);

	long long int rk = k;

	for (i = 0; i < n; ++i)
	{
		scanf("%lld", &a[i]);
		if(rk >= 0) {
			rk -= a[i];
		}
	}
	if(rk < 0) {
		cl(n, k);	
	}
	else {
		printf("-1\n");
	}

	return 0;
}