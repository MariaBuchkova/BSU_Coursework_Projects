#include <iostream>
#include<vector>
#include <iomanip>
#include <numeric>
#include <limits>

void PrintVector(const std::vector<int>& v, const std::string& msg) {
    std::cout << msg;
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << std::setw(4) << v[i];
    }
}
int EnterNum(const std::string& msg) {
    std::cout << msg;
    int a;
    std::cin >> a;
    if (!(std::cin)) {
        throw "Error! This is not a number\n";
    }
    return a;
}
void IsNotZero(int x, const char* msg) { 
    if (x == 0) { 
        throw msg;
    } 
}
size_t FindAndCount (std::vector<int>& vec, int a){
    size_t counter = 0;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] == a) {
            ++counter;
        }
    }
    return counter;
}
void ReplacingZero(std::vector<int>& vec){
    int arg = std::accumulate(vec.begin(), vec.end(), 0) / vec.size();
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] == 0) { 
            vec[i] = arg;
        }
    }
}
int main() {
    std::vector<int> number;
    int a;
    std::cout << "Enter element of vector: (for end enter not number)\n";
    while (std::cin >> a) { 
        number.push_back(a);
    }

    try {
        IsNotZero(number.size(), "Error! Vector size is 0");
        PrintVector(number, "Vector:\n");

        std::cout << "\nSum of element vector = " << std::accumulate(number.begin(), number.end(), 0);

        std::cout << "\nThe number of all elements: " << number.size();

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        int b = EnterNum("\nEnter the number with which the vector elements will be compared: ");
        //что-то непонятное с условием
        std::cout << "\nThe number of elements of the " << b << " is equal to: " << FindAndCount(number, b);
        //переделать

        ReplacingZero(number);
        PrintVector(number, "\nVector after replacing zeros: \n");

        int c = EnterNum("\nEnter lower limit: ");
        if (c >= number.size()) {
            throw "Error! Vector out of bounds";
        }
        if (c < 0) {
            throw"Error! The number must not be negative";
        }
        int d = EnterNum("\nEnter upper limit: ");
        if (d >= number.size()) {
            throw "Error! Vector out of bounds";
        }
        if (d < 0) {
            throw"Error! The number must not be negative";
        }
        if (c > d) { 
            std::swap(c, d);
        }
        int arg = std::accumulate(number.begin() + c, number.begin() + d + 1, 0);
        for (size_t i = 0; i < number.size(); ++i) {
            number[i] += arg;
        }
        PrintVector(number, "Vector after adding the interval sum:\n");
    }
    catch (const char* msg) {
        std::cerr << msg;
        return 1;
    }
    return 0;
}