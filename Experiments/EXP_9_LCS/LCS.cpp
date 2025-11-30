#include <bits/stdc++.h>
using namespace std;

int main() {
    string X = "ABCBDA";
    string Y = "BDCABA";

    int m = X.size();
    int n = Y.size();

    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    vector<vector<char>> dir(m+1, vector<char>(n+1, '0')); 
    // 'd' = diagonal, 'u' = up, 'l' = left, '0' = no direction

    // Build DP table
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(X[i-1] == Y[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                dir[i][j] = 'd';  // diagonal arrow
            } else if(dp[i-1][j] >= dp[i][j-1]) {
                dp[i][j] = dp[i-1][j];
                dir[i][j] = 'u';  // up arrow
            } else {
                dp[i][j] = dp[i][j-1];
                dir[i][j] = 'l';  // left arrow
            }
        }
    }

    cout << "\nDP TABLE\n\n";
    cout << "       ";
    for(char c : Y) cout << setw(4) << c;
    cout << "\n";

    for(int i = 0; i <= m; i++) {
        if(i == 0) cout << "   ";
        else cout << " " << X[i-1] << " ";

        for(int j = 0; j <= n; j++) {
            char arrow = ' ';

            if(dir[i][j] == 'd') arrow = '\\';   // ↖ diagonal
            else if(dir[i][j] == 'u') arrow = '^'; // ↑ up
            else if(dir[i][j] == 'l') arrow = '<'; // ← left

            if(i == 0 || j == 0) arrow = ' ';  // First row/column

            cout << setw(2) << dp[i][j] << arrow << " ";
        }
        cout << "\n";
    }

    // Reconstruct LCS
    string lcs = "";
    int i = m, j = n;
    while(i > 0 && j > 0) {
        if(dir[i][j] == 'd') {
            lcs.push_back(X[i-1]);
            i--; j--;
        } else if(dir[i][j] == 'u') {
            i--;
        } else {
            j--;
        }
    }
    reverse(lcs.begin(), lcs.end());

    cout << "\nLCS = " << lcs << "\n";

    return 0;
}
