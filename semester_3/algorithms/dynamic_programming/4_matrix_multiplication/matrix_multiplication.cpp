#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {

    std::ifstream in("input.txt");
    int n;
    in >> n;
    std::vector <int>size(2*n, 0);
    for (int i = 0;i < size.size();++i) {
        in >> size[i];
    } // ni = i*2, mi = ni+1 = i*2+1, mi+1 =  2*(i+1)+1

    std::vector<std::vector<long long>> a(n, std::vector<long long>(n, 0));
    for (int i=n-1;i>=0;--i){
        for (int j = i+1;j<n;++j) {
            a[i][j] = LLONG_MAX;
            for (int k = i;k < j;++k) {
                long long res = a[i][k] + a[k+1][j] + (long long)size[i * 2] * size[k * 2 + 1] * size[j * 2+1];
                a[i][j] = std::min(res, (a[i][j]));
            }
        }
    }
    std::ofstream out("output.txt");
    out << a[0][n - 1];
    out.close();
}