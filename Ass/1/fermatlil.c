#include <stdio.h>

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

int main() {
	long long int base, pow/*, mod = 1e9 + 7*/, mod;

	scanf("%lld %lld", &base, &mod);
	if(base != mod) {
		printf("Inverse is: %lld\n", pwo(base, mod-2, mod));	
	}
	else {
		printf("No inverse\n");
	}
	
	return 0;
}