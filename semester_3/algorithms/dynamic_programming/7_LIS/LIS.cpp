#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include<string>

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int n;
    in >> n;
    std::vector<int> F;

    for (int i = 0; i < n; ++i) {
        int x;
        in >> x;

        auto it = std::lower_bound(F.begin(), F.end(), x);

        if (it != F.end() && *it == x) continue;

        if (it == F.end()) F.push_back(x);
        else *it = x;
    }

    out << F.size() << std::endl;
    out.close();
    return 0  ;
}