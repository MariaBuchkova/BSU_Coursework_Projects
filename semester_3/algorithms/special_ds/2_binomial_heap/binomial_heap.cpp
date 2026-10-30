#include <iostream>
#include <fstream>
#include <vector>

int main() {

    //std::ios_base::sync_with_stdio(false);
    //std::cin.tie(nullptr);

    std::ifstream in("input.txt");
    long long n;
    in >> n;
    std::ofstream out("output.txt");
    int s = 0;
    while (n != 0) {
        if (n & 1) {
            out << s << '\n';
        }
        n >>= 1;
        ++s;
    }
    out.close();

    return 0;
}