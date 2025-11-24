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
std::vector<std::string> ReadDataFromFile(const std::string& inputFileName) {
	std::ifstream in(inputFileName);
	CheckInFile(in);
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(in, line)) {
		lines.push_back(line);
	}
	return lines;
}
std::string FindLengthPalindrome(const std::string& text) {
	
}
MaxPalindromes CollectLongestPalindromes(std::vector<std::string> lines) {
	MaxPalindromes result;
	for (size_t i = 0; i < lines.size(); ++i) {
		std::string palindrom = FindLengthPalindrome(lines[i]);
		if (palindrom.size() > result.size) {
			result.vecStr.clear();
			result.size = palindrom.size();
			result.vecStr.push_back(lines[i]);
			result.vecPal.push_back(palindrom);
		}
		else {
			if (palindrom.size() == result.size) {
				result.vecStr.push_back(lines[i]);
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
		const std::string inputFileName = "input.txt";
		std::vector<std::string>text = ReadDataFromFile(inputFileName);
		MaxPalindromes result = CollectLongestPalindromes(text);

		
	}
	catch (const char* msg) {
		std::cerr << msg;
		return 1;
	}
	return 0;
}