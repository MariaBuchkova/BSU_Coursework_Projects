#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include<string>

int main() {
    std::ifstream in("input.txt");

    std::string line;
    std::getline(in, line);
    std::vector<char>A(line.begin(), line.end());

    std::vector<char>B(A);
    std::reverse(B.begin(), B.end());
    int k = A.size();


    std::vector<std::vector<int>> dp(k+1, std::vector<int>(k+1, 0));
    for (int j = 1;j <= k;++j) {
        for (int i = 1; i <= k;++i) {
            if (A[i-1] == B[j-1]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    std::ofstream out("output.txt");
    out << dp[k][k]<<std::endl;

    std::vector<int>way_a;
    std::vector<int>way_b;

    for (int i = k, j = k; (i>0)&&(j>0);){
        if (A[i - 1] == B[j - 1]) {
            way_a.push_back(i - 1);
            way_b.push_back(k-j);
            i -= 1;
            j -= 1;
        }
        else {
            if (dp[i][j] == dp[i - 1][j]) i -= 1;
            else j -= 1;
        }
    }
    std::reverse(way_a.begin(), way_a.end());
    std::reverse(way_b.begin(), way_b.end());

    int p = (way_a.size() - 1) / 2;
    if (way_a[p] < way_b[p]) {
        for (int i = 0; i <= p; ++i) {
            out << A[way_a[i]];
        }
        for (int j = (int)way_a.size() - p - 2; j >= 0; --j) {
            out << A[way_b[j]];
        }
    } else {
        for (int j = (int)way_a.size() - 1; j >= (int)way_a.size() - p - 1; --j) {
            out << A[way_b[j]];
        }
        for (int i = p + 1; i < (int)way_a.size(); ++i) {
            out << A[way_a[i]];
        }
    }
    out.close();
    return 0;
}