#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
const int x = 1000000007;

int main() {

    int n, k;
    std::cin >> n; std::cin >> k;
    std::vector<int> a(k+1, 0);

    if (k > n - k) k = n - k;

    a[0] = 1;
    for (int j = 0;j < n;++j) {
        for (int i = std::min(k,j+1); i >=1;--i) {
            a[i] = ((a[i - 1] % x) + (a[i] % x)) % x;
        }
    }

    std::cout << a[k] << '\n';

    return 0;
}