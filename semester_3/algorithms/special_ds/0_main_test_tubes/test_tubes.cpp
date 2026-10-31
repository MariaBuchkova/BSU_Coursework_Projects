#include <iostream>
#include <fstream>
#include <vector>

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::ifstream in("in.txt");
    int n, m;
    in >> n; in >>m; 

    std::vector<std::vector<int>> a(n, std::vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            in >> a[i][j];
        }
    }

    std::vector<int> st;
    int x;

    for (int i = 0; i < m; ++i) {
        in >> x;
        while (!st.empty() && a[st.back() - 1][x - 1] != 0) {
            x = a[st.back() - 1][x - 1];
            st.pop_back();
        }
        st.push_back(x);
    }

    std::ofstream out("out.txt");

    for (int i = (int)st.size() - 1; i >= 0; --i) {
        out << st[i];
        if (i != 0) out << " ";
    }

    out.close();

    return 0;
}