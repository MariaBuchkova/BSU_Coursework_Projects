#include <iostream>
#include <string>
#include <vector>


bool IsPalindrome(const std::string& words) {
	for (size_t i = 0; i < words.size() / 2; ++i) {
		if (words[i] != words[words.size() - 1 - i]) {
			return false;
		}
	}
}
int main() {
	std::string str;
	std::cout << "Enter words that are separated only by  ,  ;  . ?  !  \n";
	//если между словами или знаками препинания и словом стоит пробел, то этот пробел будет считаться частью слова
	std::getline(std::cin, str);
	
	return 0;
}