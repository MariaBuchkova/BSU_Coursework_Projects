#include <iostream>
#include <fstream>
void OpeningFile(std::ifstream& file) {
	if (!file) {
		throw "Error file not open";
	}
}
void EmptyFile(std::ifstream& file) {
	if (!file.good()) {
		throw "Error file empty";
	}
}
int main() {
	try {
		std::ifstream file("proverka.txt", std::ios::in);
		OpeningFile(file); EmptyFile(file);
	}
	catch (const char* message) {
		std::cerr << message;
	}
}