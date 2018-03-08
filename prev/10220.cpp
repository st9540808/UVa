#include <iostream>
#include <algorithm>
#include <vector>
#include <array>

std::array<std::vector<int>, 1001> factorial;


std::vector<int> multiply(int n, std::vector<int>& b) {
	std::vector<int> result;
	
	int size = b.size();
	int res, carry = 0;
	for (int i = 0; i < size; i++) {
		res = carry + n * b[i];
		result.push_back(res % 10);
		carry = res / 10;
	}
	while (carry != 0) {
		result.push_back(carry % 10);
		carry /= 10;
	}
	
	return result;
}

std::vector<int>& get_factorial(int n) {
	if (factorial.at(n).empty())
		factorial.at(n) = multiply(n, get_factorial(n - 1));
	return factorial.at(n);
}


int main()
{
	factorial.at(1) = {1};
	factorial.at(2) = {2};

	int n;
	while (std::cin >> n) {
		auto vec = get_factorial(n);
		int sum = 0;
		std::for_each(vec.begin(), vec.end(), [&sum](int n){ sum += n; });
		std::cout << sum << "\n";
	}

	return 0;
}
