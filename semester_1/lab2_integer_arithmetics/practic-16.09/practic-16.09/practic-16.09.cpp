﻿//задание номер 6
#include <iostream>
#include <cmath>

int main()
{
	int n, i = 1, k = 1;

	std::cout << "enter a integer n = "; std::cin >> n;

	while (!(std::cin) || (n <= 0))
	{
		if (!(std::cin))
		{
			std::cout << "Error is not a number";
			break;
		}
		std::cout << "eror, enter an integer greater than zero n = ";
		std::cin >> n;
	}

	for (; k <= n; i += 1)
	{
		k = pow(2, i) - 1;
		if (k > n)
		{
			return 0;
		}
		std::cout << k << " ";
	}



	return 0;
}