#include <iostream>
#include <set>
#include <cmath>

void CheckInNum(int value) {
    if (!(std::cin)) {
        throw "Error! This is not a number\n";
    }
    if (value <= 0) {
        throw "Error! This is a negative number!\n";
    }
}

int main() {
    try {
        int n;
        std::cout << "Enter n: ";
        std::cin >> n;
        CheckInNum(n);
        if (n == 1) {
            throw"There are no prime numbers less than 1";
        }

        std::set<int> numbers;
        for (int i = 2; i <= n; i++) {
            numbers.insert(i);
        }

        int limit = static_cast<int>(std::sqrt(n));

        for (int p = 2; p <= limit; p++) {
            if (numbers.find(p) != numbers.end()) {
                for (int multiple = p * p; multiple <= n; multiple += p) {
                    numbers.erase(multiple);
                }
            }
        }

        std::cout << "Prime numbers up to " << n << ":\n";
        for (int prime : numbers) {
            std::cout << prime << ' ';
        }
        std::cout << '\n';

        return 0;
    }
    catch (const char* msg) {
        std::cerr << msg;
        return 1;
    }
}