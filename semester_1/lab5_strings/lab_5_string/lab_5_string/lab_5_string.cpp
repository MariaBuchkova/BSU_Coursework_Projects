#include <iostream>
#include <string>
#include <vector>
void CheckEmptyString(std::string text) {
	if (text.empty()) {
		throw "Error! The inputed string is empty.";
	}
}
void InputString(std::string& text) {
	std::getline(std::cin, text);
	CheckEmptyString(text);
}
void PrintVector(const std::vector<std::string>& vector) {
	for (size_t i = 0; i < vector.size(); i++) {
		std::cout << vector[i] << " ";
	}
	std::cout << "\n";
}
bool IsPalindrome(const std::string& word) {
	for (size_t i = 0; i < word.size() / 2; ++i) {
		if (word[i] != word[word.size() - 1 - i]) {
			return false;
		}
	}
	return true;
}
std::vector<std::string> FindPalindromeWords(const std::string& text, const std::string& delimiters) {
	if (!text.empty() && text.find_first_not_of(delimiters, 0) == std::string::npos) {
		throw"Error! text consists only of delimiters";
	}
	std::vector<std::string> palindromes;
	std::string::size_type begIndex, endIndex = 0;
	while ((begIndex = text.find_first_not_of(delimiters, endIndex)) != std::string::npos) {
		endIndex = text.find_first_of(delimiters, begIndex);
		std::string word = text.substr(begIndex, endIndex - begIndex);
		if (!word.empty() && IsPalindrome(word)) {
			palindromes.push_back(word);
		}
	}
	if (palindromes.empty()) {
		throw "There are no palindromic words in this string";
	}
	return palindromes;
}
std::string FindLongestWord(std::vector<std::string>& words) {
	std::string longestWords;
	size_t maxLength = words[0].size();
	longestWords = words[0];
	for (size_t i = 1; i < words.size(); ++i) {
		if (words[i].size() > maxLength) {           
			longestWords = words[i];   
			maxLength = words[i].size();
		}
		else {
			if (words[i].size() == maxLength) {
				longestWords = longestWords + ", " + words[i];
			}
		}
	}
	return longestWords;
}
int main() {
	std::string line, delimiters;
	try {
		std::cout << "Enter your delimiters: ";
		InputString(delimiters);

		std::cout << "Enter words that are separated only by " << delimiters << "\n";
		InputString(line);

		std::vector<std::string> pWords = FindPalindromeWords(line, delimiters);
		std::string LongestPWords = FindLongestWord(pWords);

		std::cout << "The longest palindromic words: \n";
		std::cout << LongestPWords;
	}
	catch(const char* msg){
		std::cerr << msg;
	}
	return 0;
}