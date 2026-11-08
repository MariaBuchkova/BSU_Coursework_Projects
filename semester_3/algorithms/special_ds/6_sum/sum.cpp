#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

int main() {

    int n;
    cin >> n;
    int k = sqrt(n);
    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int m = (n + k - 1) / k;
    std::vector<long long> b(m, 0);
    for (int i = 0; i < n; ++i) {
        b[i / k] += a[i];
    }

    int q;
    cin >> q;
    for (int t = 0; t < q; ++t) {
        string type;
        cin >> type;
        if (type == "Add") {
            int i;
            long long x;
            cin >> i >> x;
            a[i] += x;
            b[i / k] += x;
        } else {
            int l, r;
            cin >> l >> r;
            int jl = l / k;
            int jr = r / k;
            long long s = 0;
            if (jl == jr) {
                for (int i = l; i < r; ++i) {
                    s += a[i];
                }
            } else {
                for (int i = l; i < (jl + 1) * k; ++i) {
                    s += a[i];
                }
                for (int j = jl + 1; j < jr; ++j) {
                    s += b[j];
                }
                for (int i = jr * k; i < r; ++i) {
                    s += a[i];
                }
            }
            cout << s << "\n";
        }
    }

    return 0;
}