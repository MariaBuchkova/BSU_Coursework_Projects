#include <iostream>
#include <fstream>
#include <vector>

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::ifstream in("huffman.in");
    int n; in >> n;
    std::vector<int> a(n);
    for (int i = 0;i<n;i++){
        in >> a[i];
    }
    std::vector<long long> b;
    long long sum = 0;
    int i = 0, j = 0;

    for (int count = 0; count < n - 1; ++count) {
        long long x, y;

        if (i < n && (j >= (int)b.size() || a[i] <= b[j])) {
            x = a[i];
            i++;
        } else {
            x = b[j];
            j++;
        }

        if (i < n && (j >= (int)b.size() || a[i] <= b[j])) {
            y = a[i];
            i++;
        } else {
            y = b[j];
            j++;
        }


        b.push_back(x + y);
        sum += x + y;
    }

    std::ofstream out("huffman.out");
    out << sum;
    out.close();

    return 0;
}