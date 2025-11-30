#include <iostream>
#include <vector>
#include <ctime> // for clock() timing

using namespace std;

// Simple custom swap function (no need for extra includes)
template<typename T>
void mySwap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

// Function to generate input data
vector<int> generateInput(int n, string type) {
    vector<int> arr(n);
    if (type == "ascending") {
        for (int i = 0; i < n; i++) arr[i] = i;
    } 
    else if (type == "descending") {
        for (int i = 0; i < n; i++) arr[i] = n - i;
    } 
    else if (type == "random") {
        for (int i = 0; i < n; i++) arr[i] = rand() % n;
    }
    return arr;
}

// Bubble Sort implementation
void bubbleSort(vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                mySwap(arr[j], arr[j + 1]); // using our own swap
                swapped = true;
            }
        }
        if (!swapped) break; // optimization
    }
}

int main() {
    srand(time(0));
    vector<int> sizes = {10000, 50000, 100000};
    vector<string> patterns = {"ascending", "descending", "random"};

    for (int size : sizes) {
        cout << "\nSorting " << size << " elements\n";
        for (string pattern : patterns) {
            vector<int> arr = generateInput(size, pattern);

            cout << pattern << endl;

            clock_t start = clock();
            bubbleSort(arr);
            clock_t end = clock();

            double time_taken = double(end - start) / CLOCKS_PER_SEC;
            cout << "Time Taken : " << time_taken << " seconds\n";
        }
    }

    return 0;
}
