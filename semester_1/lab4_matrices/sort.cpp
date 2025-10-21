#include<iostream>
#include<random>
void print_matrix(int** matrix, int num_line, int num_columns)
{
	std::cout << "\n";
	for (int i = 0; i < num_line; ++i)
	{
		for (int j = 0; j < num_columns; ++j)
		{
			std::cout << matrix[i][j] << " | ";
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
	{
		delete[] matrix[i];
	}
	delete[] matrix;
	matrix = nullptr;
}
void delete_and_exit(int** matrix, int num_line) {
	delete_matrix(matrix, num_line);
	exit(1);
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
		std::mt19937 gen(45218965); // фиксированный seed
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

void bubble_sort(int** a, int n, int m, int yb)
{
	bool swaped;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m - 1; ++j)
		{
			swaped = false;
			for (int k = 0; k < m - 1 - j; ++k)
			{
				if (yb)
				{
					if (a[i][k] > a[i][k + 1])
					{
						std::swap(a[i][k], a[i][k + 1]);
						swaped = true;
					}
				}
				else
				{
					if (a[i][k] < a[i][k + 1])
					{
						std::swap(a[i][k], a[i][k + 1]);
						swaped = true;
					}
				}
			}
			if (!swaped) break;
		}
	}
	std::cout << "bubble sort matrix:";
	print_matrix(a, n, m);
}
void insert_sort(int** mat, int n, int m, int yb)
{
	for (int k = 0; k < n; ++k)
	{
		for (int i = 1; i < m; ++i)
		{
			int x = mat[k][i];
			if (yb)
			{
				for (int j = i - 1; j >= 0 && mat[k][j] > x; --j)
				{
					mat[k][j + 1] = mat[k][j];
					mat[k][j] = x;
				}
			}
			else 
			{
				for (int j = i - 1; j > 0 && mat[k][j] < x; --j)
				{
					mat[k][j + 1] = mat[k][j];
					mat[k][j] = x;
				}
			}
		}
	}
	std::cout << "insert sort matrix:";
	print_matrix(mat, n, m);
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
	std::cout<<"Enter 1 - bubble\nEnter 2 - insert\nEnter 3 - count\nEnter 4 - merge\n";
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

		break;
	}
	case 4:
	{

		break;
	}
	default:
		std::cout << "Error, the entered number does not match the selection options\n";
		delete_and_exit(mat, n);
	}
}