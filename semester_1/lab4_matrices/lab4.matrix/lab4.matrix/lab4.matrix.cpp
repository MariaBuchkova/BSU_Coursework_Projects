//задание 5; все функции написаны для квадратной матрицы

#include<iostream>
#include<random>
#include <iomanip>
void print_matrix(int** matrix, int num_line)
{
	std::cout << "\n";
	for (int i = 0; i < num_line; ++i)
	{
		for (int j = 0; j < num_line; ++j)
		{
			std::cout << std::setw(4) << matrix[i][j];
		}
		std::cout << "\n";
	}
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
void cin_input_matrix(int** matrix, int num_line)
{
	std::cout << "\n";
	for (int i = 0; i < num_line; ++i)
	{
		std::cout << "enter " << i + 1 << " line of matrix: \n";
		for (int j = 0; j < num_line; ++j)
		{
			std::cin >> matrix[i][j];
		}
		std::cout << "\n";
	}
	std::cout << "original matrix: ";
	print_matrix(matrix, num_line);
}
void delete_matrix(int** matrix, int num_line)
{
	for (int i = 0; i < num_line; ++i)
		delete[] matrix[i];
	delete[] matrix;
}
void check_letter()
{
	if (!(std::cin))
	{
		throw "Error! This is not a number\n";
	}
}
void check_nonpositive(int value)
{
	if (value <= 0)
	{
		throw "Error! This is a negative number!\n";
	}
}
void input_int(int& integer)
{
	std::cin >> integer;
	check_letter();
}
void enter_num_line(int& num_line)
{
	std::cout << "Enter number of lines: ";
	std::cin >> num_line;
	check_letter();
	check_nonpositive(num_line);
}
void input_matrix_choice(int** matrix, int num_line, std::mt19937& gen) {
	std::cout << "Enter the array randomly? ( 1 - true; 0 - false )\n";
	std::cout << "----------> ";
	int ran_or_not;
	input_int(ran_or_not);
	switch (ran_or_not) {
	case 0: {
		for (int i = 0; i < num_line; ++i) {
			std::cout << "enter " << i + 1 << " line of matrix: \n";
			for (int j = 0; j < num_line; ++j) {
				input_int(matrix[i][j]);
			}
			std::cout << "\n";
		}
		std::cout << "original matrix: ";
		print_matrix(matrix, num_line);
		break;
	}
	case 1: {
		int lower_lim;
		std::cout << "enter the lower limit: ";
		input_int(lower_lim);
		int upper_lim;
		std::cout << "enter the upper limit: ";
		input_int(upper_lim);
		if (lower_lim > upper_lim) {
			std::swap(lower_lim, upper_lim);
		}
		std::uniform_int_distribution<int> dist(lower_lim, upper_lim);
		for (int i = 0; i < num_line; ++i) {
			for (int j = 0; j < num_line; ++j) {
				matrix[i][j] = dist(gen);
			}
		}
		print_matrix(matrix, num_line);
		break;
	}
	default:
		throw "Error, only 1 or 0!\n";
	}
}
int main()
{
	int num_line = 0;
	int** matrix = nullptr;
	try {
		enter_num_line(num_line);
		matrix = din_memory_matrix(num_line);
		std::mt19937 gen(45218965);
		input_matrix_choice(matrix, num_line, gen);
		//нижний правый треугольник с диагональю
		int max_triangle_el = matrix[0][num_line - 1];
		int i_max_el = 0, j_max_el = 0; //для следующего задания
		for (int i = 1; i < num_line; ++i)
		{
			for (int j = num_line - 2; j >= num_line - i - 1; --j)
			{
				if (matrix[i][j] > max_triangle_el)
				{
					max_triangle_el = matrix[i][j];
					i_max_el = i, j_max_el = j; //для следующего задания
				}
			}
		}
		std::cout << "the maximum element of the lower right triangle of the matrix = " << max_triangle_el;
		//оставшаяся часть матрицы
		int max_el = max_triangle_el;
		for (int i = 0; i < num_line - 1; ++i)
		{
			for (int j = 0; j < num_line - i; ++j)
			{
				if (matrix[i][j] > max_el)
				{
					max_el = matrix[i][j];
					i_max_el = i, j_max_el = j;
				}
			}
		}
		if (max_el > 0)
		{
			std::cout << "\nMax positiv element in matrix: " << max_el << " in position: " << i_max_el + 1 << ", " << j_max_el + 1;
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
		else
		{
			throw "\nError: There are no positive elements in the array.";
		}
		delete_matrix(matrix, num_line);
		matrix = nullptr;
	}
	catch (const char* msg) {
		std::cerr << msg;
	}
	if (matrix) {
		delete_matrix(matrix, num_line);
		matrix = nullptr;
	}
	return 0;
}