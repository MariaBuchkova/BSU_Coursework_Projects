#include <iostream>
#include <random>
#include <cmath>
int main() {
	int const N_MAX = 1000;
	int n, t = -1, nomer = -1;
	double a[N_MAX], mod_a[N_MAX];
	double min_mod, sum = 0, lower_lim, upper_lim, for_transfer, p;
	int ran_or_not;
	std::cout << "Enter the number of elements in the array not exceeding 1000 \n";
	std::cout << "----------> ";
	std::cin >> n; 
	if (!(std::cin) || (n <= 0) || (n > 1000))
	{
		std::cout << "You're a STUPID person. they asked for a NON-NEGATIVE integer not exceeding 1000, and WHAT DID YOU ENTER!? ERROR!!! BEGIN AGAIN!";
		return 0;
	}
	std::cout << "Enter the array randomly? ( 1 - true; 0 - false )\n"; 
	std::cout << "----------> ";
	std::cin >> ran_or_not;
	if (!(std::cin) || (!(ran_or_not == 1)&&!(ran_or_not == 0)))
	{
		std::cout << "ONLY 1 OR 0! BEGIN AGAIN! ";
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
	for (int i = 0; i < n; i++)
	{
		mod_a[i] = std::fabs(a[i]);
		std::cout << a[i] << "   ";
	}
	min_mod = mod_a[0];
	bool more_then_one = false;
	for (int i = 1; i < n; i++)
	{
		if (min_mod == mod_a[i])
		{
			more_then_one = true;
			nomer = i + 1;
		}
		if (min_mod >= mod_a[i]) 
		{
			min_mod = mod_a[i]; 
		}
	}
	std::cout << "\n" << "minimal in absolute value: " << min_mod ;
	if (more_then_one == true)
	{
		std::cout << "\nmax nomer: " << nomer;

	}

	for (int i = 0; i < n; i++)
	{
		if (a[i] < 0)
		{
			t = i + 1;
			break;
		}
	}
	if (t > -1)
	{
		for (; t < n; t++)
		{
			sum = sum + a[t];
		}
		std::cout << "\nsum = " << sum;
	}
	else
	{
		std::cout << "\nThere are no negative elements in the array, it is impossible to calculate the sum";
	}

	std::cout << "\nEnter the numbers you want to delete: "; 
	std::cin >> p;
	int k = 0; 
	for (int i = 0; i < n; i++) {
		if (a[i] != p) {
			a[k] = a[i];
			k++;
		}
	}
	for (int i = k; i < n; i++) {
		a[i] = 0;
	}
	std::cout << "final array: ";
	for (int i = 0; i < n; i++)
		std::cout << a[i] << " ";
	return 0;
}