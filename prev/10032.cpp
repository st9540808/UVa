#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cstring>


unsigned long long dp[22501];

int main(void) {
	int n;
	std::cin >> n;
	
	for (int i = 0; i < n; i++) {
		int size, W;
		
		std::cin >> size;
		std::vector<int> weight(size);
		std::for_each(weight.begin(), weight.end(),
					  [](int& w){ std::cin >> w; });

		std::memset(dp, 0, sizeof dp);
		W = std::accumulate(weight.begin(), weight.end(), 0);

		dp[0] = 1;
		for (int i = 0; i < size; i++) {
			for (int j = W / 2; j >= weight[i]; j--) {
				dp[j] = dp[j - weight[i]] << 1 | dp[j];
			}
		}
		
		if (size % 2 == 0) {
			for (int j = W / 2; j >= 0; j--) {
				if (dp[j] & (1ull << size / 2)) {
					std::cout << j << " " << W - j << "\n";
					break;
				}
			}
		} else {
			for (int j = W / 2; j >= 0; j--) {
				if (dp[j] & (1ull << size / 2) ||
					dp[j] & (1ull << size / 2 + 1)) {
					std::cout << j << " " << W - j << "\n";
					break;
				}
			}
		}

		if (i != n - 1) std::cout << "\n";
	}

	return 0;
}