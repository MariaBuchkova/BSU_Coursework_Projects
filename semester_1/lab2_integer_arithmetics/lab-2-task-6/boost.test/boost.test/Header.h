#pragma once
#include <iostream>
#include <cmath>
#include <vector>

std::vector<int> fun(int n)
{
	int k = 1; 
	std::vector<int> num;
	for (int p = 2; ; p++)
	{ 
		bool is_prime = true;
		for (int i = 2; i * i <= p; i++)
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