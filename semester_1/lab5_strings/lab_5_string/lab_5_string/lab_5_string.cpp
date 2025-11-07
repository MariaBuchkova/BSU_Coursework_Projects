#include <iostream>
#include <string>
#include <vector>
void EmptyString(std::string text) {
	if (text.empty()) {
		throw "Error! The inputed string is empty.";
	}
}
void InputString(std::string& text) {
	std::getline(std::cin, text);
	EmptyString(text);
}
void PrintVector(const std::vector<std::string>& vector) {
	for (int i = 0; i < vector.size(); i++) {
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
std::vector<std::string> FindPalindromeWords(const std::string& text, const std::string& delimeters) {
	if (!text.empty() && text.find_first_not_of(delimeters, 0) == std::string::npos) {
		throw"Error! text consists only of delimiters";
	}
	std::vector<std::string> palindromWords;
	std::string::size_type begIndex, endIndex = 0;
	while ((begIndex = text.find_first_not_of(delimeters, endIndex)) != std::string::npos) {
		endIndex = text.find_first_of(delimeters, begIndex);
		std::string word = text.substr(begIndex, endIndex - begIndex);
		if (!word.empty() && IsPalindrome(word)) {
			palindromWords.push_back(word);
		}
	}
	if (palindromWords.empty()) {
		throw "there are no palindromic words in this string";
	}
	return palindromWords;
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
	std::string str, dlm;
	try {
		std::cout << "Enter your delimeters: ";
		InputString(dlm);
		std::cout << "Enter words that are separated only by " << dlm << "\n";
		InputString(str);
		std::vector<std::string> pWords = FindPalindromeWords(str, dlm);
		std::cout << "palindromes: \n";
		PrintVector(pWords);
		std::cout << "The longest palindromic words: \n";
		std::string maxPWords = FindLongestWord(pWords);
		std::cout << maxPWords;
	}
	catch(const char* msg){
		std::cerr << msg << "\n";
	}
	return 0;
}