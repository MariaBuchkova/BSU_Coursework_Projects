#include <iostream>


int main() {
	int n, m, min, i;
	std::cout << "enter n = ";
	std::cin >> n;
	std::cout << "enter m = ";
	std::cin >> m;
	if (n <= 0 || m <= 0) {
		std::cout << "eror 404";
		return 0;
	}



	if (n < m) {
		min = n;
	}
	else {
		min = m;
	}

	for (i = 2; i <= min; i += 1) {
		if (n % i == 0 && m % i == 0) {
			std::cout << i <<" ";
		}
	}

	return 0;
}