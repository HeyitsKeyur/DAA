#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 5;  // number of stations

    // Example input (matches your diagram)
    int a1[] = {7, 9, 3, 4, 8};
    int a2[] = {8, 5, 6, 4, 5};
    int t1[] = {2, 3, 1, 3};
    int t2[] = {2, 1, 2, 2};
    int e1 = 2, e2 = 4;
    int x1 = 3, x2 = 2;

    vector<int> f1(n), f2(n), l1(n), l2(n);

    // Step 1: Initialize first station
    f1[0] = e1 + a1[0];
    f2[0] = e2 + a2[0];

    // Step 2: Compute the values
    for (int j = 1; j < n; j++) {
        if (f1[j - 1] + a1[j] <= f2[j - 1] + t2[j - 1] + a1[j]) {
            f1[j] = f1[j - 1] + a1[j];
            l1[j] = 1;
        } else {
            f1[j] = f2[j - 1] + t2[j - 1] + a1[j];
            l1[j] = 2;
        }

        if (f2[j - 1] + a2[j] <= f1[j - 1] + t1[j - 1] + a2[j]) {
            f2[j] = f2[j - 1] + a2[j];
            l2[j] = 2;
        } else {
            f2[j] = f1[j - 1] + t1[j - 1] + a2[j];
            l2[j] = 1;
        }
    }

    // Step 3: Compute final time and line
    int f_star, l_star;
    if (f1[n - 1] + x1 <= f2[n - 1] + x2) {
        f_star = f1[n - 1] + x1;
        l_star = 1;
    } else {
        f_star = f2[n - 1] + x2;
        l_star = 2;
    }

    // Step 4: Backtrack to find path
    vector<int> line(n);
    line[n - 1] = l_star;
    for (int j = n - 1; j > 0; j--) {
        if (line[j] == 1)
            line[j - 1] = l1[j];
        else
            line[j - 1] = l2[j];
    }

    // Step 5: Print table similar to the image
    cout << "\nAssembly Line Scheduling DP Table\n";
    cout << "--------------------------------------------\n";
    cout << "       ";
    for (int j = 0; j < n; j++) cout << setw(8) << j + 1;
    cout << "\n--------------------------------------------\n";

    cout << "f1/l1  ";
    for (int j = 0; j < n; j++) {
        cout << setw(6) << f1[j] << "[" << l1[j] << "]";
    }
    cout << "\n";

    cout << "f2/l2  ";
    for (int j = 0; j < n; j++) {
        cout << setw(6) << f2[j] << "[" << l2[j] << "]";
    }
    cout << "\n--------------------------------------------\n";

    cout << "l* = " << l_star << "\n";
    cout << "Minimum total time (f*) = " << f_star << "\n";

    cout << "\nSelected Line Path:\n";
    for (int j = 0; j < n; j++) {
        cout << "Station " << j + 1 << " → Line " << line[j] << "\n";
    }

    return 0;
}