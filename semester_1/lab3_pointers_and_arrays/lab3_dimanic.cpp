#include <iostream>
#include <random>
#include <cmath>
int main() {
	int num_of_elements, nomer = -1, index_neg_el = -1;
	double* array;
	double max_mod, sum = 0, lower_lim, upper_lim, for_transfer, add_el, neg_el = 1;
	int ran_or_not;
	std::cout << "Enter the number of elements in the array: \n";
	std::cout << "----------> ";
	std::cin >> num_of_elements;
	if (!(std::cin) || (num_of_elements <= 0) )
	{
		std::cout << "EROR! Enter not negativ integer number";
		return 1;
	}
	array = new double[num_of_elements + 1];
	std::cout << "Enter the array randomly? ( 1 - true; 0 - false )\n";
	std::cout << "----------> ";
	std::cin >> ran_or_not;
	if (!(std::cin) || (!(ran_or_not == 1) && !(ran_or_not == 0)))
	{
		std::cout << "Error! only 1 or 0";
		delete[] array;
		return 1;
	}
	if (ran_or_not == 0)
	{
		for (int i = 0; i < num_of_elements; i++)
		{
			std::cout << "enter " << i + 1 << " element of array ";
			std::cin >> array[i];
			if (!(std::cin))
			{
				std::cout << "Error! This is not number";
				delete[] array;
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
			delete[] array;
			return 1;
		}
		std::cin >> upper_lim;
		if (!(std::cin))
		{
			std::cout << "Error! This is not number";
			delete[] array;
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
		for (int i = 0; i < num_of_elements; i++)
		{
			array[i] = dist(gen);
		}
	}
	std::cout << "array:\n";
	max_mod = std::fabs(array[0]);
	bool more_then_one = false;
	for (int i = 1; i < num_of_elements; i++)
	{
		if (max_mod == std::fabs(array[i]))
		{
			more_then_one = true;
		}
		if (max_mod < std::fabs(array[i]))
		{
			max_mod = std::fabs(array[i]);
			nomer = i + 1;
		}
	}
	for (int i = 0; i < num_of_elements; i++)
	{
		std::cout << array[i] << "   ";
	}
	std::cout << "\n" << "max in absolute value: " << max_mod;
	if (more_then_one == true)
	{
		std::cout << "\nmin nomer: " << nomer;

	}
	if (array[0] > 0)
	{
		std::cout << "\nIn this array the first number is positive, it is impossible to calculate the sum";
	}
	else
	{
		sum = array[0];
		for (int i = 1; i < num_of_elements; i++)
		{
			if (array[i] > 0)
			{
				break;
			}
			sum = sum + array[i];
		}
		std::cout << "\nsum = " << sum;
	}
	for (int i = 0; i < num_of_elements; i++)
	{
		if (array[i] < 0)
		{
			neg_el = array[i];
			index_neg_el = i;
		}
	}
	if (neg_el == 1)
	{
		std::cout << "\nThere is no negative element for add p. end of program.";
	}
	else
	{
		std::cout << "\nEnter the numbers you want to add: ";
		std::cin >> add_el;
		if (!(std::cin))
		{
			std::cout << "Error! This is not number";
			delete[] array;
			return 1;
		}
		for (int j_end = num_of_elements; j_end != index_neg_el; --j_end)
		{
			array[j_end] = array[j_end - 1];
		}
		array[index_neg_el + 1] = add_el;
		std::cout << "final array: ";
		for (int i = 0; i < num_of_elements + 1; i++)
			std::cout << array[i] << "   ";
	}
	delete[] array;
	return 0;
}