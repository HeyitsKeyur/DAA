#include <iostream>
#include <vector>
#include <iomanip>
#include <climits>
using namespace std;

void matrixChainOrder(const vector<int>& p) {
    int n = p.size() - 1;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

    for (int L = 2; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    // Print DP Table in matrix-style format
    cout << "\nMatrix Chain Multiplication DP Table:\n";
    cout << "--------------------------------------\n\n";

    // Print column headers
    cout << setw(6) << " ";
    for (int j = 1; j <= n; j++)
        cout << setw(6) << j;
    cout << "\n";

    // Print rows
    for (int i = 1; i <=n; i++) {
        cout << setw(3) << i << " "; // row index
        for (int j = 1; j <= n; j++) {
            if (i > j)
                cout << setw(6) << "-";
            else
                cout << setw(6) << dp[i][j];
        }
        cout << "\n";
    }

    cout << "\nMinimum number of multiplications is: " << dp[1][n] << endl;
}

int main() {
    // Example: 6 matrices
    // Dimensions: A1(30x35), A2(35x15), A3(15x5), A4(5x10), A5(10x20), A6(20x25)
    vector<int> p = {30, 35, 15, 5, 10, 20, 25};

    matrixChainOrder(p);

    return 0;
}
