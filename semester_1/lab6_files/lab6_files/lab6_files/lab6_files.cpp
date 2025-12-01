#include <fstream>
#include <iostream>
#include <string>
#include <vector>
void CheckInFile(std::ifstream& filename){
	if (!filename) {
		throw"Error! InFile not open";
	}
	if (filename.peek() == std::ifstream::traits_type::eof()) {
		throw"Error! File is empty";
	}
}
void PrintVector(const std::vector<std::string>& vector) {
	for (int i = 0; i < vector.size(); i++) {
		std::cout << vector[i] << " ";
	}
	std::cout << "\n";
}
std::vector<std::string> ReadDataFromFile(const std::string& inFileName) {
	std::ifstream in(inFileName);
	CheckInFile(in);
	std::vector<std::string> lines;
	std::string line;
	while (getline(in, line)) {
		lines.push_back(line);
	}
	in.close();
	return lines;
}
std::vector<std::string> FindLengthNum(const std::vector<std::string>& text) {
	int max = -1;
	int x = 0;
	std::vector<std::string> maxline;
	for (size_t i = 0; i < text.size(); ++i) {
		for (size_t j = 0; j < text[i].size(); ++j) {
			x = 0;
			while (isdigit(text[i][j])) {
				++x;
				++j;
			}
			if (x == max) {
				maxline.push_back(text[i]);
			}
			if (x > max && x > 0) {
				max = x;
				maxline.clear();
				maxline.push_back(text[i]);
			}
		}
	}
	if (maxline.empty()) { 
		throw"Error! not find number in file";
	}
	return maxline;
}
void PrintAnswer(const std::string& outFileName, const std::vector<std::string>& text) {
	std::ofstream out(outFileName);
	if (!out) throw"Error! InFile not open";
	out << "The first 10 lines containing the longest substring consisting only of numbers:";
	for (size_t i = 0; i < text.size() && i < 10; ++i) {
		out << "\n" << i + 1 << ": " << text[i];
	}
	out.close();
}
int main() {
	try {
		const std::string inputFileName = "input.txt";
		std::vector<std::string>text = ReadDataFromFile(inputFileName);
		std::vector<std::string> lineWithMaxsNum = FindLengthNum(text);

		const std::string outFileName = "output.txt";
		PrintAnswer(outFileName, lineWithMaxsNum);

		std::cout << "The process is complete, the result is in your file out.txt";
	}
	catch (const char* msg) {
		std::cerr << msg;
		return 1;
	}
	return 0;
}