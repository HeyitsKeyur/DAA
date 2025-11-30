#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// Function to find minimum number of coins/notes
void makeChange(int amount, vector<int> denominations) {
    // Sort denominations in descending order
    sort(denominations.rbegin(), denominations.rend());

    cout << "Amount to be changed: " << amount << endl;
    cout << "Coins/Notes used: ";

    int totalCoins = 0;
    for (int coin : denominations) {
        if (amount >= coin) {
            int count = amount / coin;        // how many coins of this type
            amount -= count * coin;           // reduce the remaining amount
            totalCoins += count;              // add to total coin count

            // Print the used denomination
            for (int i = 0; i < count; i++) {
                cout << coin << " ";
            }
        }
    }

    cout << "\nTotal coins/notes used = " << totalCoins << endl;
}

int main() {
    
    vector<int> denominations = {1, 2, 5, 10, 20, 50, 100, 500, 2000};

    int amount;
    cout << "Enter amount: ";
    cin >> amount;

    makeChange(amount, denominations);

    return 0;
}
