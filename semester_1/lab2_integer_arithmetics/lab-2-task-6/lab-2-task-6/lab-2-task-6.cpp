//задание номер 6
#include <iostream>
#include <cmath>

int main()
{
	int n, k = 1; //n - вводим с клавиатуры; k - простые числа Мерсена;
	std::cout << "enter a integer n = "; std::cin >> n;
	if (!(std::cin) || (n <= 0))
	{
			std::cout << "You're a STUPID person. they asked for a NON-NEGATIVE integer, and WHAT DID YOU ENTER!? ERROR!!!!!!!!!!!!!!!!!!!!!!!!";
			return 0;
	}
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

			std::cout << k << " ";
		}
	}
	return 0;
}