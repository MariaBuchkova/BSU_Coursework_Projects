#pragma once
#include <iostream>
#include <cmath>
#include <vector>

std::vector<int> fun(int n)
{
	int k = 1; //n - ââîäèì ñ êëàâèàòóðû; k - ïðîñòûå ÷èñëà Ìåðñåíà;
	std::vector<int> num;
	for (int p = 2; ; p++)  //p - ïðîñòîé ïîêàçàòåëü ñòåïåíè;
	{ 
		bool is_prime = true;  //is_prime - ïðîñòîå èëè íåò 
		for (int i = 2; i * i <= p; i++) //ñ ïîìîùüþ i ïåðåáèðàåì äåëèòåëè p
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