#include <iostream>
#include <random>
#include <cmath>
int main() {
	int const N_MAX = 1000;
	int num_of_element, index_neg_el = -1, nomer = -1;
	double array[N_MAX];
	double min_mod, sum = 0, lower_lim, upper_lim, for_transfer, add_el;
	int ran_or_not;
	std::cout << "Enter the number of elements in the array not exceeding 1000 \n";
	std::cout << "----------> ";
	std::cin >> num_of_element; 
	if (!(std::cin) || (num_of_element <= 0) || (num_of_element > 1000))
	{
		std::cout << "EROR! Enter not negativ integer number";
		return 1;
	}
	std::cout << "Enter the array randomly? ( 1 - true; 0 - false )\n"; 
	std::cout << "----------> ";
	std::cin >> ran_or_not;
	if (!(std::cin) || (!(ran_or_not == 1)&&!(ran_or_not == 0)))
	{
		std::cout << "Error! only 1 or 0 ";
		return 1;
	}
	if (ran_or_not == 0) 
	{
		for (int i = 0; i < num_of_element; i++)
		{
			std::cout << "enter " << i + 1 << " element of array ";
			std::cin >> array[i]; 
			if (!(std::cin))
			{
				std::cout << "Error! This is not number";
				return 1;
			}
		}
	}
	else
	{
		srand(static_cast<unsigned>(time(0)));
		std::cout << "enter the element limit\n";
		std::cin >> lower_lim;
		if (!(std::cin))
		{
			std::cout << "Error! This is not number";
			return 1;
		}
		std::cin >> upper_lim;
		if (!(std::cin))
		{
			std::cout << "Error! This is not number";
				return 1;
		}
		if (lower_lim > upper_lim)
		{
			for_transfer = lower_lim;
			lower_lim = upper_lim;
			upper_lim = for_transfer;
		}
		std::mt19937 gen(45218965);
		std::uniform_real_distribution<double> dist(lower_lim, upper_lim);
		for (int i = 0; i < num_of_element; i++)
		{
			array[i] = dist(gen);
		}
	}
	std::cout << "array:\n";
	min_mod = std::fabs(array[0]);
	bool more_then_one = false;
	for (int i = 1; i < num_of_element; i++)
	{
		if (min_mod == std::fabs(array[i]))
		{
			more_then_one = true;
			nomer = i + 1;
		}
		if (min_mod >= std::fabs(array[i]))
		{
			min_mod = std::fabs(array[i]);
		}
	}
	for (int i = 0; i < num_of_element; i++)
	{
		std::cout << array[i] << "   ";
	}
	std::cout << "\n" << "minimal in absolute value: " << min_mod ;
	if (more_then_one == true)
	{
		std::cout << "\nmax nomer: " << nomer;

	}

	for (int i = 0; i < num_of_element; i++)
	{
		if (array[i] < 0)
		{
			index_neg_el = i + 1;
			break;
		}
	}
	if (index_neg_el > -1)
	{
		for (; index_neg_el < num_of_element; index_neg_el++)
		{
			sum = sum + array[index_neg_el];
		}
		std::cout << "\nsum = " << sum;
	}
	else
	{
		std::cout << "\nThere are no negative elements in the array, it is impossible to calculate the sum";
	}

	std::cout << "\nEnter the numbers you want to delete: "; 
	std::cin >> add_el;
	if (!(std::cin))
	{
		std::cout << "Error! This is not number";
		return 1;
	}
	int k = 0; 
	for (int i = 0; i < num_of_element; i++) {
		if (std::fabs (array[i] - add_el) > 0.00001) {
			array[k] = array[i];
			k++;
		}
	}
	for (int i = k; i < num_of_element; i++) {
		array[i] = 0;
	}
	std::cout << "final array: ";
	for (int i = 0; i < num_of_element; i++)
		std::cout << array[i] << " ";
	return 0;
} 