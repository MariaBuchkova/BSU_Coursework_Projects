#include <fstream>
#include <iostream>
#include <string>
#include <vector>
struct MaxPalindromes {
	std::string::size_type size = 0;
	std::vector<std::string> vecStr, vecPal;
};
void CheckInFile(std::ifstream& file){
	if (!file) {
		throw"Error! InFile not open";
	}
	if (file.peek() == std::ifstream::traits_type::eof()) {
		throw"Error! File is empty";
	}
}
void PrintVector(const std::vector<std::string>& vector) {
	for (int i = 0; i < vector.size(); i++) {
		std::cout << vector[i] << " ";
	}
	std::cout << "\n";
}

std::string FindLeghtPalindrom(const std::string& text) {
	
}
MaxPalindromes CollectLongestPalindromes(std::ifstream& InFile) {
	MaxPalindromes result;
	std::string line;
	while (std::getline(InFile, line)) {
		std::string palindrom = FindLeghtPalindrom(line);
		if (palindrom.size() > result.size) {
			result.vecStr.clear();
			result.size = palindrom.size();
			result.vecStr.push_back(line);
			result.vecPal.push_back(palindrom);
		}
		else {
			if (palindrom.size() == result.size) {
				result.vecStr.push_back(line);
				result.vecPal.push_back(palindrom);
			}
		}
	}
	if (result.size == 0) {
		throw"There are no palindromic substrings in this file.";
	}
	return result;
}
int main() {
	try {
		std::ifstream InFile("input.txt");
		CheckInFile(InFile);
		MaxPalindromes result = CollectLongestPalindromes(InFile);

		InFile.close();
	}
	catch (const char* msg) {
		std::cerr << msg;
		return 1;
	}
	return 0;
}