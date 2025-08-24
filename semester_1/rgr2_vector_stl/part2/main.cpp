#include "time_utility.h"
#include "train.h"

#include <iostream>

int main() {

    using namespace time_utility;

    std::random_device rd;
    std::mt19937 generator(rd());

    std::time_t t1 = SetTime(12, 23);
    try {
        t1 = SetTime(12, 60);
    } catch (const std::out_of_range& err) {
        std::cerr << err.what() << std::endl;
    }

    std::time_t t2 = GenerateRandomTime(generator);

    std::cout << "t1: ";
    PrintTime(t1);

    std::cout << '\n';
    
    std::cout << "t2: ";
    PrintTime(t2);
    std::cout << '\n';
    
    std::cout << "t1 < t2: " << std::boolalpha << CompareTimes(t1, t2) << '\n';
    std::cout << "t2 < t1: " << std::boolalpha << CompareTimes(t2, t1) << '\n';



    return EXIT_SUCCESS;
}
