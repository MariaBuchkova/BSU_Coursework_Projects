#include<iostream>
#include<random>
#include <iomanip>
#include <cstdlib>
void print_matrix(int** matrix, int num_line, int num_columns)
{
	std::cout << "\n";
	for (int i = 0; i < num_line; ++i)
	{
		for (int j = 0; j < num_columns; ++j)
		{
			std::cout << std::setw(4) << matrix[i][j];
		}
		std::cout << "\n";
	}
}
int** din_memory_matrix(int num_line, int num_columns)
{
	int** matrix = new int* [num_line];
	for (int i = 0; i < num_line; ++i)
	{
		matrix[i] = new int[num_columns];
	}
	return matrix;
}
void input_matrix(int** matrix, int num_line, int num_columns)
{
	std::cout << "\n";
	for (int i = 0; i < num_line; ++i)
	{
		std::cout << "enter " << i + 1 << " line of matrix: \n";
		for (int j = 0; j < num_columns; ++j)
		{
			std::cin >> matrix[i][j];
		}
		std::cout << "\n";
	}
	std::cout << "original matrix: ";
	print_matrix(matrix, num_line, num_columns);
}
void delete_matrix(int** matrix, int num_line)
{
	for (int i = 0; i < num_line; ++i)
		delete[] matrix[i];
	delete[] matrix;
}

void delete_and_exit(int** matrix, int num_line)
{
	delete_matrix(matrix, num_line);
	std::exit(EXIT_FAILURE);
}
bool check_letter()
{
	if (!(std::cin))
	{
		std::cout << "Error! This is not a number\n";
		return true;
	}
	return false;
}

bool check_negotiv(int value)
{
	if (value <= 0)
	{
		std::cout << "Error! This is a negative number!\n";
		return true;
	}
	return false;
}

bool enter_num_line_columns(int& num_line, int& num_columns)
{
	std::cout << "Enter number of lines: ";
	std::cin >> num_line;
	if (check_letter() || check_negotiv(num_line))
		return false;

	std::cout << "Enter number of columns: ";
	std::cin >> num_columns;
	if (check_letter() || check_negotiv(num_columns))
		return false;

	return true;
}
void matrix_input(int** matrix, int num_line, int num_columns) {
	int ran_or_not;
	std::cout << "Enter the array randomly? ( 1 - true; 0 - false )\n";
	std::cout << "----------> ";
	std::cin >> ran_or_not;
	if (check_letter()) {
		delete_and_exit(matrix, num_line);
	}
	switch (ran_or_not) {
	case 0: {
		bool find_error = false;
		for (int i = 0; i < num_line && !find_error; ++i) {
			std::cout << "enter " << i + 1 << " line of matrix: \n";
			for (int j = 0; j < num_columns && !find_error; ++j) {
				std::cin >> matrix[i][j];
				if (check_letter()) {
					find_error = true;
					break;
				}
			}
			std::cout << "\n";
		}
		if (find_error) {
			delete_and_exit(matrix, num_line);
		}
		std::cout << "original matrix: ";
		print_matrix(matrix, num_line, num_columns);
		break;
	}
	case 1: {
		int lower_lim;
		std::cout << "enter the lower limit: ";
		std::cin >> lower_lim;
		if (check_letter()) {
			delete_and_exit(matrix, num_line);
		}
		int upper_lim;
		std::cout << "enter the upper limit: ";
		std::cin >> upper_lim;
		if (check_letter()) {
			delete_and_exit(matrix, num_line);
		}
		if (lower_lim > upper_lim) {
			std::swap(lower_lim, upper_lim);
		}
		std::mt19937 gen(45218965);
		std::uniform_int_distribution<int> dist(lower_lim, upper_lim);
		for (int i = 0; i < num_line; ++i) {
			for (int j = 0; j < num_columns; ++j) {
				matrix[i][j] = dist(gen);
			}
		}
		print_matrix(matrix, num_line, num_columns);
		break;
	}
	default:
		std::cout << "Error, only 1 or 0!\n";
		delete_and_exit(matrix, num_line);
	}
}

//----------------------------------------------------------------------->

void bubble_sort(int** matrix, int num_line, int num_columns, int descending)
{
	bool swaped;
	for (int i = 0; i < num_line; ++i)
	{
		for (int j = 0; j < num_columns - 1; ++j)
		{
			swaped = false;
			for (int k = 0; k < num_columns - 1 - j; ++k)
			{
				if (descending)
				{
					if (matrix[i][k] > matrix[i][k + 1])
					{
						std::swap(matrix[i][k], matrix[i][k + 1]);
						swaped = true;
					}
				}
				else
				{
					if (matrix[i][k] < matrix[i][k + 1])
					{
						std::swap(matrix[i][k], matrix[i][k + 1]);
						swaped = true;
					}
				}
			}
			if (!swaped) break;
		}
	}
	std::cout << "bubble sort matrix:";
	print_matrix(matrix, num_line, num_columns);
}
void insert_sort(int** matrix, int num_line, int num_columns, int descending)
{
	for (int i = 0; i < num_line; ++i)
	{
		for (int j = 1; j < num_columns; ++j)
		{
			int x = matrix[i][j];
			int k = j - 1;

			if (descending)
			{
				while (k >= 0 && matrix[i][k] > x)
				{
					matrix[i][k + 1] = matrix[i][k];
					--k;
				}
			}
			else
			{
				while (k >= 0 && matrix[i][k] < x)
				{
					matrix[i][k + 1] = matrix[i][k];
					--k;
				}
			}
			matrix[i][k + 1] = x;
		}
	}
	std::cout << "insert sort matrix:";
	print_matrix(matrix, num_line, num_columns);
}
void counter_sort(int** matrix, int num_line, int num_columns, int descending)
{
	int* count = new int[100];
	for (int i = 0; i < num_line; ++i)
	{
		for (int j = 0; j < 100; ++j)
		{
			count[j] = 0;
		}
		for (int j = 0; j < num_columns; ++j)
		{
			if (matrix[i][j] < 0 || matrix[i][j] >= 100)
			{
				std::cout << "Invalid value in " << i + 1 << " line; " << j + 1 << " column: " << matrix[i][j];
				delete[] count;
				delete_and_exit(matrix, num_line);
			}
			++count[matrix[i][j]];
		}
		int k = 0;
		if (descending)
		{
			for (int j = 0; j < 100; ++j)
			{
				while (count[j] != 0)
				{
					matrix[i][k++] = j;
					--count[j];
				}
			}
		}
		else
		{
			for (int j = 99; j > -1; --j)
			{
				while (count[j] != 0)
				{
					matrix[i][k++] = j;
					--count[j];
				}
			}
		}
	}
	delete[] count;
	std::cout << "count sort matrix:";
	print_matrix(matrix, num_line, num_columns);
}
void merge(int** matrix, int left, int mid, int right, int num_line, int row_index, int** sort_matrix, int descending)
{
	int i = left;
	int j = mid;
	int k = left;
	while (i < mid && j < right)
	{
		if (descending) {
			if (matrix[row_index][i] <= matrix[row_index][j])
			{
				sort_matrix[row_index][k++] = matrix[row_index][i++];
			}
			else
			{	
				sort_matrix[row_index][k++] = matrix[row_index][j++];
			}
		}
		else
		{
			if (matrix[row_index][i] >= matrix[row_index][j])
			{
				sort_matrix[row_index][k++] = matrix[row_index][i++];
			}
			else
			{
				sort_matrix[row_index][k++] = matrix[row_index][j++];
			}
		}
	}
	while (i < mid)
	{
		sort_matrix[row_index][k++] = matrix[row_index][i++];
	}
	while (j < right)
	{
		sort_matrix[row_index][k++] = matrix[row_index][j++];
	}

	for (int t = left; t < right; t++)
	{
		matrix[row_index][t] = sort_matrix[row_index][t];
	}
}
void merge_sort(int** matrix, int left, int right, int num_line, int** sort_matrix, int descending)
{
	if (right - left <= 1) return;
	for (int row_index = 0; row_index < num_line; ++row_index)
	{
		int mid = (left + right) / 2;

		merge_sort(matrix, left, mid, num_line, sort_matrix, descending);
		merge_sort(matrix, mid, right, num_line, sort_matrix, descending);

		merge(matrix, left, mid, right, num_line, row_index, sort_matrix, descending);
	}
}

int main()
{
	int n = 0, m = 0;
	if (!enter_num_line_columns(n, m))
		return 1;
	int** mat = din_memory_matrix(n, m);
	matrix_input(mat, n, m);
	std::cout << "How would you like to sort? (Enter 1 if descending, 0 if ascending): ";
	int yb;
	std::cin >> yb;
	if (check_letter()) {
		delete_and_exit(mat, n);
	}
	if (!((yb == 0)||(yb == 1)))
	{
		std::cout << "Error, only 1 or 0!";
		delete_and_exit(mat, n);
	}
	int sort;
	std::cout << "Select how you want to sort the lines:\n";
	std::cout<<"Enter 1 - bubble\nEnter 2 - insert\nEnter 3 - count (only possible for numbers from 0 to 99)\nEnter 4 - merge\n";
	std::cout << "enter an option: ";
	std::cin >> sort;
	if (check_letter()) {
		delete_and_exit(mat, n);
	}
	switch (sort)
	{
	case 1: 
	{
		bubble_sort(mat, n, m, yb);
		break;
	}
	case 2:
	{
		insert_sort(mat, n, m, yb);
		break;
	}
	case 3:
	{
		counter_sort(mat, n, m, yb);
		break;
	}
	case 4:
	{
		int** ar = din_memory_matrix(n, m);
		int f = 0;
		merge_sort(mat, f, m, n, ar, yb);
		std::cout << "merge sort matrix:";
		print_matrix(mat, n, m);
		delete_matrix(ar, n);
		break;
	}
	default:
		std::cout << "Error, the entered number does not match the selection options\n";
		delete_and_exit(mat, n);
	}
	delete_matrix(mat, n);
}