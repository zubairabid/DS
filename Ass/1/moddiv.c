#include <stdio.h>
long long int mod = 1e9 + 7;

long long int pwo(long long int base, long long int pow, long long int mod) {
	long long int res = 1;
	
	while(pow > 0) {
	
		if(pow % 2 == 1) {
			pow--;
			res = (res * base)%mod;
		}
	
		pow /= 2;
		base = (base * base)%mod;
	
	}

	return res;
}

long long int minv(long long int a) {

	if(a != mod) {
		return (pwo(a, mod-2, mod))%mod;	
	}
	else {
		return -1;
	}
	
	return 0;
}

int main() {
	long long int a, b;
	scanf("%lld %lld", &a, &b);
	a = a % mod;
	printf("Result of modular division is %lld\n", (a*minv(b))%mod);
}