#include <iostream>
#include <random>
void delete_matrix(int** matrix, int num_line)
{
	for (int i = 0; i < num_line; ++i)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
	matrix = nullptr;
}
int** din_memory_matrix(int num_line)
{
	int** matrix = new int* [num_line];
	for (int i = 0; i < num_line; ++i)
	{
		matrix[i] = new int[num_line];
	}
	return matrix;
}
void print_matrix(int** matrix, int num_line)
{
	std::cout << "\n";
	for (int i = 0; i < num_line; ++i)
	{
		for (int j = 0; j < num_line; ++j)
		{
			std::cout << matrix[i][j] << " | ";
		}
		std::cout << "\n";
	}
}
bool check_letter()
{
	if (!(std::cin))
	{
		std::cout << "Error! This is not number";
		return 1;
	}
	else
	{
		return 0;
	}
}
bool check_negotiv(int something)
{
	if (something<=0)
	{
		std::cout << "Error! This is negotive number!";
		return 1;
	}
	else
	{
		return 0;
	}
}
int main(){
	int num_line, ran_or_not;
	std::cout << "Enter the number of lines and columns in the array: \n";
	std::cout << "----------> ";
	std::cin >> num_line;
	if (check_letter() || check_negotiv(num_line))
	{
		return 1;
	}
	int** matrix = din_memory_matrix(num_line);
	std::cout << "Enter the array randomly? ( 1 - true; 0 - false )\n";
	std::cout << "----------> ";
	std::cin >> ran_or_not;
	if (check_letter())
	{
		delete_matrix(matrix, num_line);
		return 1;
	}
	switch (ran_or_not)
	{
	case 0:
	{
		bool find_error = false;
		for (int i = 0; i < num_line && !find_error; ++i)
		{
			std::cout << "enter " << i + 1 << " line of matrix: \n";
			for (int j = 0; j < num_line && !find_error; ++j)
			{
				std::cin >> matrix[i][j];
				if (check_letter())
				{
					find_error = true;
					break;
				}
			}
			std::cout << "\n";
		}
		if (find_error)
		{
			delete_matrix(matrix, num_line);
			break;
		}
		std::cout << "original matrix: ";
		print_matrix(matrix, num_line);
		break;
	}
	case 1:
	{
		srand(static_cast<unsigned>(time(0)));
		int lower_lim;
		std::cout << "enter the lower limit: ";
		std::cin >> lower_lim;
		if (check_letter())
		{
			delete_matrix(matrix, num_line);
			return 1;
		}
		int upper_lim;
		std::cout << "enter the upper limit: ";
		std::cin >> upper_lim;
		if (check_letter())
		{
			delete_matrix(matrix, num_line);
			return 1;
		}
		if (lower_lim > upper_lim)
		{
			std::swap(lower_lim, upper_lim);
		}
		std::mt19937 gen(45218965);
		std::uniform_int_distribution<int> dist(lower_lim, upper_lim);
		for (int i = 0; i < num_line; ++i)
		{
			for (int j = 0; j < num_line; ++j)
			{
				matrix[i][j] = dist(gen);
			}
		}
		print_matrix(matrix, num_line);
		break;
	}
	default:
		std::cout << "Error, only 1 or 0!";
		delete_matrix(matrix, num_line);
		return 1;
	}
	int max_triangle_el = matrix[1][num_line - 1];
	int i_max_el = 0, j_max_el = 0;
	for (int i = 2; i < num_line; ++i)
	{
		std::cout << "\n";
		for (int j = num_line - 2; j > num_line - i - 1; --j)
		{
			if (matrix[i][j] > max_triangle_el)
			{
				max_triangle_el = matrix[i][j];
			}
		}
	}
	std::cout << "the maximum element of the lower right triangle of the matrix = " << max_triangle_el;
	int max_el = matrix[0][0];
	for (int i = 0; i < num_line; ++i)
	{
		for (int j = 0; j < num_line; ++j)
		{
			if (matrix[i][j] > max_el)
			{
				max_el = matrix[i][j];
				i_max_el = i, j_max_el = j;
			}
		}
	}
	for (int j = 0; j < num_line; ++j)
	{
		std::swap(matrix[0][j], matrix[i_max_el][j]);
	}
	for (int i = 0; i < num_line; ++i)
	{
		std::swap(matrix[i][0], matrix[i][j_max_el]);
	}
	std::cout << "\nnew matrix: \n";
	print_matrix(matrix, num_line);
}