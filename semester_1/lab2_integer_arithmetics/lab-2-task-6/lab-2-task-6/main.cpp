#include<iostream>
#include "Header.h"

int main() {
	try {
		int n;
		std::cout << "Enter positive number: ";
		std::cin >> n;
		if (!std::cin) throw "Error: You entered the wrong number.";
		if (n <= 0) throw"Error: You entered a negative number or zero.";
		std::vector<int> num = fun(n);
		if (num.empty()) throw"Merson number less than not found n.";
		std::cout << "Result:\n";
		for (int i = 0; i < num.size(); i++) {
			std::cout << num[i] << ' ';
		}
		std::cout << '\n';
	}
	catch (const char* msg) {
		std::cout << msg;
	}
}