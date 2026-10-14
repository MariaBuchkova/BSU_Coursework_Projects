#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include<string>


int main() {
	std::ifstream in("in.txt");

	std::string A, B;
	long long x, y, z;
	in >> x >> y >> z >> A >> B;

	std::vector<std::vector<long long>> dp(A.size() + 1, std::vector<long long>(B.size() + 1, 0));

	for (int i = 1; i <= A.size(); ++i) {
		dp[i][0] = dp[i - 1][0] + x;
	}

	for (int j = 1; j <= B.size(); ++j) {
		dp[0][j] = dp[0][j - 1] + y;
	}

	for (int i = 1; i <= A.size(); ++i) {
		for (int j = 1; j <= B.size(); ++j) {
			long long diag = dp[i - 1][j - 1];
			if (A[i - 1] != B[j - 1]) diag += z;

			dp[i][j] = std::min(diag, std::min(dp[i - 1][j] + x, dp[i][j - 1] + y));
		}
	}
	std::ofstream out("out.txt");

	out << dp[A.size()][B.size()] << std::endl;
	out.close();
		return 0  ;
}