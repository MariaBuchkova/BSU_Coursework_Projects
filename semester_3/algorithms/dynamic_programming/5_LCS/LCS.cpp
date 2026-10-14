#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {
    int k;
    std::cin >> k;
    std::vector<int>A(k);
    for (int i = 0;i < k;++i) {
        std::cin >> A[i];
    }
    std::vector<int>B(k);
    for (int i = 0;i < k;++i) {
        std::cin >> B[i];
    }

    std::vector<std::vector<int>> dp(k+1, std::vector<int>(k+1, 0));
    for (int j = 1;j <= k;++j) {
        for (int i = 1; i <= k;++i) {
            if (A[i-1] == B[j-1]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    std::cout << dp[k][k]<<std::endl;

    std::vector<int>way_a;
    std::vector<int>way_b;

    for (int i = k, j = k; (i>0)&&(j>0);){
        if (A[i - 1] == B[j - 1]) {
            way_a.push_back(i - 1);
            way_b.push_back(j - 1);
            i -= 1;
            j -= 1;
        }
        else {
            if (dp[i][j] == dp[i - 1][j]) i -= 1;
            else j -= 1;
        }
    }
    std::reverse(way_a.begin(), way_a.end());
    for (int i = 0;i < way_a.size();++i) {
        std::cout << way_a[i]<<' ';
    }
    std::cout << std::endl;
    std::reverse(way_b.begin(), way_b.end());
    for (int i = 0;i < way_b.size();++i) {
        std::cout << way_b[i]<<' ';
    }
}