#include <iostream>
#include<vector>
#include <iomanip>
#include <numeric>
#include <string>
#include <algorithm>

void PrintVector(const std::vector<int>& arr) {
    size_t size = arr.size();
    for (size_t i = 0; i < size; ++i) {
        std::cout << std::setw(4) << arr[i];
    }
}
void SizeNotZero(int size) { 
    if (size == 0) { 
        throw "Error size must be positive";
    } 
}
bool CheckBorder (int lower, int upper, size_t size){
    if (upper >= size || lower < 0) {
        return false;
    }
    return true;
}
void RemovingDuplicates(std::vector<int>& arr){
    for (size_t i = 0; i < arr.size(); ++i) {
        for (size_t j = i + 1; j < arr.size();) {
            if (abs(arr[i]) == abs(arr[j])) {
                arr.erase(arr.begin() + j);
            }
            else {
                j++;
            }
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
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    try {
        SizeNotZero(number.size());
        std::cout << "Vector:\n";
        PrintVector(number);
    }
    catch (const char* msg) {
        std::cerr << msg;
        return 1;
    }

    std::vector<int>::iterator begin = number.begin();
    std::vector<int>::iterator end = number.end();

    int64_t sum = std::accumulate(begin, end, 0);
    int64_t size = number.size();

    std::cout << "\nSum of element vector = " << sum;
    std::cout << "\nThe number of all elements: " << size;

    int value = 3;
    std::cout << "\nThe number of elements of the " << value << "is equal to: "
        << std::count_if(begin, end, [value](int x) {return x == value; });
    std::cout << "\nThe number of elements is less than zero: "
        << std::count_if(begin, end, [](int x) {return x < 0; });

    int64_t arg = sum / size;
    std::vector<int> first(number);
    std::replace_if(first.begin(), first.end(), [](int x) {return x == 0; }, arg);
    std::cout << "\nVector after replacing zeros: \n";
    PrintVector(first);

    int lower = 0;
    int upper = 2;
    std::vector<int> second(number);
    if (!CheckBorder(lower, upper, size)) {
        std::cout << "\nThe interval[" <<
            lower << "; " << upper << "] extends beyond the vector boundaries";
    }
    else {
        int64_t sumInterwal = std::accumulate(begin + lower, begin + upper + 1, 0);
        for (size_t i = 0; i < size; ++i) {
            second[i] += sumInterwal;
        }
        std::cout << "\nInterval sum[" << lower << "; " << upper << "]: " << sumInterwal;
        std::cout << "\nVector after adding the interval ["
            << lower << "; " << upper << "] sum:\n";
        PrintVector(second);
    }

    std::vector<int> third(number);
    int min = *std::min_element(begin, end);
    int max = *std::max_element(begin, end);
    int difference = max - min;
    std::replace_if(third.begin(), third.end(), [](int x) {return abs(x) % 2 == 0; }, difference);
    std::cout << "\nVector after changing elements with even modulus:\n";
    PrintVector(third);

    std::vector<int> fourth(number);
    RemovingDuplicates(fourth);
    std::cout << "\nVector after removing duplicates: \n";
    PrintVector(fourth);

    return 0;
}