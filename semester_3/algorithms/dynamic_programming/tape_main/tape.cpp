#include <fstream>
#include <vector>
#include <algorithm>

int main() {
    std::ifstream in("input.txt");
    int n;
    in >> n;

    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) in >> a[i];

    std::vector<std::vector<long long> > f(n, std::vector<long long>(n, 0));

    for (int i = 0; i < n; ++i) f[i][i] = a[i];

    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i + len <= n; ++i) {
            int j = i + len - 1;
            if (len == 2) {
                f[i][j] = std::max(a[i], a[j]);
                f[j][i] = std::min(a[i], a[j]);
            } else {
                f[i][j] = std::max(a[i] + f[j][i + 1], a[j] + f[j - 1][i]);
                f[j][i] = std::min(f[i + 1][j], f[i][j - 1]);
            }
        }
    }

    std::ofstream out("output.txt");
    out << f[0][n - 1] << "\n";
    return 0;
}