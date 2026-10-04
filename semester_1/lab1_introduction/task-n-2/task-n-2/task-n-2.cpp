#include <iostream>

int main() {
	int i, n, s = 0, p = 1;
	std::cout << "enter an integer ";
	std::cin >> n;


	if (n >= 1) {
		for (i = 1; i <= n; i = i + 2)
			p = p * i;
		for (i = 2; i <= n; i = i + 2)
			s = s + i;
		std::cout << "sum = " << s << ", work = " << p;
	}

	if (n < 0) {
		for (i = 1; i >= n; i = i - 2)
			p = p * i;
		for (i = 0; i >= n; i = i - 2)
			s = s + i;
		std::cout << "sum = " << s << ", work = " << p;

	}

	return 0;

}