//задание номер 6
#include <iostream>
#include <cmath>

int main()
{
	int n, k = 1; //n - вводим с клавиатуры; k - простые числа Мерсена;
	std::cout << "enter a integer n = "; std::cin >> n;
	if (!(std::cin) || (n <= 0))
	{
			std::cout << "You're a stupid person, they asked for a non-negative integer, and what did you enter? ERROR!!!!!!!!!!!!!!!!!!!!!!!!";
			return 0;
	}
	for (int p = 2; ; p++)  
	{ 
		bool is_prime = true;  //p - простой показатель степени; is prime - простое или нет 
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

			std::cout << k << " ";
		}
	}
	return 0;
}