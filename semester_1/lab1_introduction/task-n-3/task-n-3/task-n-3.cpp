#include <iostream>
#include <cmath>

int main() {
	long long n, s = 0, i;
	std::cout << "enter an integer n = "; //для больших n значение n^n очень большие и стремятся в бесконечность
	std::cin >> n;    //поэтому значение s выходит за пределы значений типа данных
	if (n <= 0) {      //и поэтому может выводится некорректное значение или выводиться inf		
		std::cout << "error 404";
		return 0;
	}
	while (n <= 0) {
		std::cout << "input error, please enter a number greater than or equal to 1, n = "; std::cin >> n;
	}


	for (i = 1; i <= n; i = i + 1) {
			s = s + pow(i, i);}

	std::cout << "sum=" << s;


	return 0;
}
