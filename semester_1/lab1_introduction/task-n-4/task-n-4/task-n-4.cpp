#include <iostream>
int main() {
	int k, p = 1, i;
	std::cout << "enter an integer k =  ";
	std::cin >> k;
	if (k <= 0) {
		std::cout << "error 404";
		return 0;
	}
	if (k % 2 == 1) {
		for (i = 1; i <= k; i += 2) {
			p = p * i;
		}
	}
	else {
		for (i = 2; i <= k; i += 2) {
			p = p * i;
		}
	}

	std::cout << "p = " << p;


	return 0;
}