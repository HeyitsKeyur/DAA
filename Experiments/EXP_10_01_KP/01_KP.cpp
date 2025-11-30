#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;

    vector<int> profit(n+1), weight(n+1);

    cout << "Enter profits of items:\n";
    for(int i = 1; i <= n; i++) cin >> profit[i];

    cout << "Enter weights of items:\n";
    for(int i = 1; i <= n; i++) cin >> weight[i];

    cout << "Enter Knapsack Capacity: ";
    cin >> W;

    // DP table
    vector<vector<int>> dp(n+1, vector<int>(W+1, 0));

    // Build DP table
    for(int i = 1; i <= n; i++) {
        for(int w = 1; w <= W; w++) {
            if(weight[i] <= w) {
                dp[i][w] = max(profit[i] + dp[i-1][w - weight[i]],
                               dp[i-1][w]);
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }

    // Print DP Table
    cout << "\n===== DP TABLE =====\n";
    
    // Header row (weights 0..W)
    cout << "     ";
    for(int w = 0; w <= W; w++)
        cout << setw(4) << w;
    cout << "\n";

    cout << "-----------------------------------------------\n";
    
    for(int i = 0; i <= n; i++) {
        cout << "i=" << i << " | ";
        for(int w = 0; w <= W; w++) {
            cout << setw(4) << dp[i][w];
        }
        cout << "\n";
    }

    cout << "\nMaximum Profit = " << dp[n][W] << "\n";

    return 0;
}