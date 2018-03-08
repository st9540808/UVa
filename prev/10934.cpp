#include <stdio.h>
#include <algorithm>
#include <limits.h>

long long F[101][64] = {0};

int bottom_up() {
	for (int k = 1; k <= 100; k++) {
		for (int trials = 1; trials <= 63; trials++)
			F[k][trials] = 1 + F[k-1][trials-1] + F[k][trials-1];
	}
}

int main()
{
	bottom_up();

	int k;
	long long n;
	while (scanf("%d%lld", &k, &n) && k != 0) {
		bool is_above_63 = true;
		for (int trials = 1; trials <= 63; trials++) {
			if (F[k][trials] >= n) {
				printf("%d\n", trials);
				is_above_63 = false;
				break;
			}
		}
		if (is_above_63)
			printf("More than 63 trials needed.\n");
	}
	
	return 0;
}
