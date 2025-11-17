//задание 5; все функции написаны для квадратной матрицы

#include<iostream>
#include<random>
#include <iomanip>
struct limits {
	int lower;
	int upper;
};
struct element {
	int item;
	int row;
	int col;
};
void CheckLetter() {
	if (!(std::cin)) {
		throw "Error! This is not a number\n";
	}
}
void CheckNonpositive(int value) {
	if (value <= 0) {
		throw "Error! This is a negative number!\n";
	}
}
void InputInt(int& integer) {
	std::cin >> integer;
	CheckLetter();
}
void EnterNumLine(int& size) {
	std::cout << "Enter number of lines: ";
	std::cin >> size;
	CheckLetter();
	CheckNonpositive(size);
}
int** InitMemoryMatrix(int size){
	int** matrix = new int* [size];
	for (int i = 0; i < size; ++i) {
		matrix[i] = new int[size];
	}
	return matrix;
}
void DeleteMemoryMatrix(int** matrix, int size) {
	for (int i = 0; i < size; ++i) {
		delete[] matrix[i];
	}
	delete[] matrix;
}
void PrintMatrix(int** matrix, int size) {
	std::cout << "\n";
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			std::cout << std::setw(4) << matrix[i][j];
		}
		std::cout << "\n";
	}
}
void InputMatrixCin(int** matrix, int size) {
	for (int i = 0; i < size; ++i) {
		std::cout << "enter " << i + 1 << " line of matrix: \n";
		for (int j = 0; j < size; ++j) {
			InputInt(matrix[i][j]);
		}
		std::cout << "\n";
	}
}
limits InputLimits() {
	limits limits;
	std::cout << "enter the lower limit: ";
	InputInt(limits.lower);
	std::cout << "enter the upper limit: ";
	InputInt(limits.upper);

	if (limits.lower > limits.upper) {
		std::swap(limits.lower, limits.upper);
	}

	return limits;
}
void InputMatrixGen(int** matrix, int size, limits lim, std::mt19937& gen) {
	std::uniform_int_distribution<int> dist(lim.lower, lim.upper);
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			matrix[i][j] = dist(gen);
		}
	}
}
void InputMatrixChoice(int** matrix, int size, std::mt19937& gen) {
	std::cout << "Enter the array randomly? ( 1 - true; 0 - false )\n";
	std::cout << "----------> ";
	int isRandom;
	InputInt(isRandom);
	switch (isRandom) {
	case 0: {
		InputMatrixCin(matrix, size);
		break;
	}
	case 1: {
		InputMatrixGen(matrix, size, InputLimits(), gen);
		break;
	}
	default:
		throw "Error, only 1 or 0!\n";
	}
}
element MaximumElementLowerRightTriangle(int** matrix, int size) {
	element maxElTriangle;
	maxElTriangle.item = matrix[0][size - 1];
	maxElTriangle.row = 0, maxElTriangle.col = size - 1;
	for (int i = 1; i < size; ++i) {
		for (int j = size - 2; j >= size - i - 1; --j) {
			if (matrix[i][j] > maxElTriangle.item) {
				maxElTriangle.item = matrix[i][j];
				maxElTriangle.row = i, maxElTriangle.col = j;
			}
		}
	}
	return maxElTriangle;
}
element MaximumElement(int** matrix, int size, element maxElTriangle) {
	element maxEl = maxElTriangle;
	for (int i = 0; i < size - 1; ++i) {
		for (int j = 0; j < size - i; ++j) {
			if (matrix[i][j] > maxEl.item) {
				maxEl.item = matrix[i][j];
				maxEl.row = i, maxEl.col = j;
			}
		}
	}
	return maxEl;
}
void SwapRowAndColWithFirst(int** matrix, int size, int rowIndex, int colIndex) {
	for (int j = 0; j < size; ++j) {
		std::swap(matrix[0][j], matrix[rowIndex][j]);
	}
	for (int i = 0; i < size; ++i) {
		std::swap(matrix[i][0], matrix[i][colIndex]);
	}
}
int main()
{
	int size = 0;
	int** matrix = nullptr;
	try {
		EnterNumLine(size);
		matrix = InitMemoryMatrix(size);
		std::mt19937 gen(45218965);
		InputMatrixChoice(matrix, size, gen);
		std::cout << "original matrix: ";
		PrintMatrix(matrix, size);
		element maxElTriangle = MaximumElementLowerRightTriangle(matrix, size);
		std::cout << "the maximum element of the lower right triangle of the matrix = " << maxElTriangle.item;
		element maxEl = MaximumElement(matrix, size, maxElTriangle);
		if (maxEl.item > 0) {
			std::cout << "\nMax positiv element in matrix: " << maxEl.item << " in position: " << maxEl.row + 1 << ", " << maxEl.col + 1;
			SwapRowAndColWithFirst(matrix, size, maxEl.row, maxEl.col);
			std::cout << "\nnew matrix: \n";
			PrintMatrix(matrix, size);
		}
		else {
			throw "\nError: There are no positive elements in the matrix.";
		}
	}
	catch (const char* msg) {
		std::cerr << msg;
	}
	DeleteMemoryMatrix(matrix, size);
	matrix = nullptr;
	return 0;
}