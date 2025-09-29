#include <iostream>
#include <random>
#include <cmath>
int main() {
	int const N_MAX = 1000;
	int n, nomer = -1, j = -1;
	double* a;
	double max_mod, sum = 0, lower_lim, upper_lim, for_transfer, p, neg_el = 1;
	int ran_or_not;
	std::cout << "Enter the number of elements in the array not exceeding 1000 \n";
	std::cout << "----------> ";
	std::cin >> n;
	if (!(std::cin) || (n <= 0) || (n > 1000))
	{
		std::cout << "You're a STUPID person. they asked for a NON-NEGATIVE integer not exceeding 1000, and WHAT DID YOU ENTER!? ERROR!!! BEGIN AGAIN!";
		return 0;
	}
	a = new double[n + 1];
	std::cout << "Enter the array randomly? ( 1 - true; 0 - false )\n";
	std::cout << "----------> ";
	std::cin >> ran_or_not;
	if (!(std::cin) || (!(ran_or_not == 1) && !(ran_or_not == 0)))
	{
		std::cout << "ONLY 1 OR 0! BEGIN AGAIN! ";
		delete[] a;
		return 0;
	}
	if (ran_or_not == 0)
	{
		for (int i = 0; i < n; i++)
		{
			std::cout << "enter " << i + 1 << " element of array ";
			std::cin >> a[i];
			if (!(std::cin))
			{
				std::cout << "You're a STUPID person. they asked for a integer, and WHAT DID YOU ENTER!? ERROR!!! BEGIN AGAIN!";
				delete[] a;
				return 0;
			}
		}
	}
	else
	{
		srand(static_cast<unsigned>(time(0)));
		std::cout << "enter the element limit\n";
		std::cin >> lower_lim;
		std::cin >> upper_lim;
		if (!(std::cin))
		{
			std::cout << "You're a STUPID person. they asked for a integer, and WHAT DID YOU ENTER!? ERROR!!! BEGIN AGAIN!";
			delete[] a;
			return 0;
		}
		if (lower_lim > upper_lim)
		{
			for_transfer = lower_lim;
			lower_lim = upper_lim;
			upper_lim = for_transfer;
		}
		std::mt19937 gen(45218965);
		std::uniform_real_distribution<double> dist(lower_lim, upper_lim);
		for (int i = 0; i < n; i++)
		{
			a[i] = dist(gen);
		}
	}
	std::cout << "array:\n";
	max_mod = std::fabs(a[0]);
	bool more_then_one = false;
	for (int i = 1; i < n; i++)
	{
		if (max_mod == std::fabs(a[i]))
		{
			more_then_one = true;
		}
		if (max_mod < std::fabs(a[i]))
		{
			max_mod = std::fabs(a[i]);
			nomer = i + 1;
		}
	}
	for (int i = 0; i < n; i++)
	{
		std::cout << a[i] << "   ";
	}
	std::cout << "\n" << "max in absolute value: " << max_mod;
	if (more_then_one == true)
	{
		std::cout << "\nmin nomer: " << nomer;

	}
	if (a[0] > 0)
	{
		std::cout << "\nIn this array the first number is positive, it is impossible to calculate the sum";
	}
	else
	{
		sum = a[0];
		for (int i = 1; i < n; i++)
		{
			if (a[i] > 0)
			{
				break;
			}
			sum = sum + a[i];
		}
		std::cout << "\nsum = " << sum;
	}
	for (int i = 0; i < n; i++)
	{
		if (a[i] < 0)
		{
			neg_el = a[i];
			j = i;
		}
	}
	if (neg_el == 1)
	{
		std::cout << "\nThere is no negative element for add p. end of program.";
	}
	else
	{
		std::cout << "\nEnter the numbers you want to add: ";
		std::cin >> p;
		if (!(std::cin))
		{
			std::cout << "You're a STUPID person. they asked for a integer, and WHAT DID YOU ENTER!? ERROR!!! BEGIN AGAIN!";
			delete[] a;
			return 0;
		}
		for (int j_end = n; j_end != j; --j_end)
		{
			a[j_end] = a[j_end - 1];
		}
		a[j + 1] = p;
		std::cout << "final array: ";
		for (int i = 0; i < n + 1; i++)
			std::cout << a[i] << "   ";
	}
	delete[] a;
	return 0;
}