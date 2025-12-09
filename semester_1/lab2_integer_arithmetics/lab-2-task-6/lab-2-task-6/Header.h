#pragma once
#include <iostream>
#include <cmath>
#include <vector>

std::vector<int> fun(int n)
{
	int k = 1; //n - вводим с клавиатуры; k - простые числа Мерсена;
	std::vector<int> num;
	for (int p = 2; ; p++)  //p - простой показатель степени;
	{ 
		bool is_prime = true;  //is_prime - простое или нет 
		for (int i = 2; i * i <= p; i++) //с помощью i перебираем делители p
		{
			if (p % i == 0) 
			{
				is_prime = false;
				break;
			}
		}
		if (is_prime) 
		{
			int k = pow(2, p) - 1;

			if (k > n) break;

			num.push_back(k);
		}
	}
	return num;
}
