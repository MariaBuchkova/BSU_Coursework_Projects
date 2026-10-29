#include <iostream>
#include <vector>
#include<fstream>

int main() {

    int n; 
    std::ifstream in("input.txt"); 
    in >> n;

    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        in >> a[i];
    }

    bool f = true;

    for (int i = 0; 2 * i + 1 < n; ++i) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (a[i] > a[l]) {
            f = false;
            break;
        }

        if (r>=n){
            break;
        }

        if (a[i] > a[r]) {
            f = false;
            break;
        }
    }
    std::ofstream out("output.txt");

    if (f) out << "Yes\n";
    else   out << "No\n";
    out.close();

    return 0;
}