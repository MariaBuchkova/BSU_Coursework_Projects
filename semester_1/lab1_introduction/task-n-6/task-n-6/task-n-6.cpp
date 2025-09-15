#include <iostream>

int main() {
	int i, n, s=0;
	std::cout << "enter an integer n = ";
	std::cin >> n;
	for (i = 1; i / 2 < n; i += 2) {
		s = i + s;

	}

	std::cout << "sum = " << s;
	return 0;
}