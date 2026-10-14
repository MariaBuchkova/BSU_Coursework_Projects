#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
const int x = 1000000007;

long long fun (long long b, int n){
    long long res = 1;
    while (n > 0) {
        if (n & 1) {
            res = (res*b)%x;
        }
        b = (b*b)%x;
        n >>= 1;
    }
    return res;
}


int main() {

    int n, k;
    std::cin >> n; std::cin >> k;
    std::vector<long long>f(n+1);
    f[0] = 1;
    for (int i = 1;i <= n;++i) {
        f[i] = (f[i - 1]%x * i)%x;
    }
    long long den = (f[n - k] % x * f[k] % x) % x;
    std::cout << ((f[n]%x) * (fun(den,x-2)%x))%x;
}