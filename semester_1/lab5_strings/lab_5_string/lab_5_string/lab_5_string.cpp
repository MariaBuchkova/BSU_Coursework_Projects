#include <iostream>
#include <string>
#include <vector>
void print_vector(const std::vector<std::string>& Words) {
	for (int i = 0; i < Words.size(); i++) {
		std::cout << Words[i] << " ";
	}
	std::cout << "\n";
}
std::vector<std::string> theLongestWord(std::vector<std::string>& words) {
	std::vector<std::string> max;
	size_t maxSize = words[0].size();
	max.push_back(words[0]);
	for (size_t i = 1; i < words.size(); ++i) {
		if (words[i].size() > maxSize) {
			max.clear();           
			max.push_back(words[i]);   
			maxSize = words[i].size();
		}
		else if (words[i].size() == maxSize) {
			max.push_back(words[i]);
		}
	}
	return max;
}
bool IsPalindrome(const std::string& word) {
	for (size_t i = 0; i < word.size() / 2; ++i) {
		if (word[i] != word[word.size() - 1 - i]) {
			return false;
		}
	}
	return true;
}
std::vector<std::string> SplitPalindromeWords(const std::string& s, const std::string& d) {
	std::vector<std::string> pWords;
	std::string::size_type b_i = s.find_first_not_of(d, 0);
	std::string::size_type e_i = s.find_first_of(d, b_i);
	while (b_i != std::string::npos) {
		std::string word = s.substr(b_i, e_i - b_i);
		if (!word.empty() && IsPalindrome(word)) {
			pWords.push_back(word);
		}
		b_i = s.find_first_not_of(d, e_i);
		if (b_i == std::string::npos) break;
		e_i = s.find_first_of(d, b_i);
	}
	return pWords;
}
int main() {
	std::string str, dlm;
	std::cout << "Enter your delimeters: ";
	std::getline(std::cin, dlm);
	std::cout << "Enter words that are separated only by " << dlm << "\n";
	//если между словами или знаками препинания и словом стоит пробел, то этот пробел будет считаться частью слова
	std::getline(std::cin, str);
	std::vector<std::string> pWords = SplitPalindromeWords(str, dlm);
	std::cout << "polindroms: \n";
	print_vector(pWords);
	std::cout << "The longest palindromic words: \n";
	std::vector<std::string> maxPWords = theLongestWord(pWords);
	print_vector(maxPWords);
	return 0;
}