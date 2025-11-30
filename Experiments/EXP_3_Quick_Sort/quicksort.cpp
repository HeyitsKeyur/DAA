#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

template<typename T>
void mySwap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

// Generate input data
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

// Partition function with pivot selection
int partitionQS(vector<int> &arr, int low, int high, const string &pivotType) {
    int pivotIndex;

    if (pivotType == "first") {
        pivotIndex = low;
    } 
    else if (pivotType == "last") {
        pivotIndex = high;
    } 
    else if (pivotType == "random") {
        pivotIndex = low + rand() % (high - low + 1);
    } 
    else { // "median"
        int mid = low + (high - low) / 2;
        int a = arr[low], b = arr[mid], c = arr[high];
        if ((a > b) != (a > c)) pivotIndex = low;
        else if ((b > a) != (b > c)) pivotIndex = mid;
        else pivotIndex = high;
    }

    int pivot = arr[pivotIndex];
    mySwap(arr[pivotIndex], arr[high]); // move pivot to end

    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            mySwap(arr[i], arr[j]);
        }
    }
    mySwap(arr[i + 1], arr[high]);
    return i + 1;
}

// Pure QuickSort (no insertion sort)
void quickSort(vector<int> &arr, int low, int high, const string &pivotType) {
    while (low < high) {
        int pi = partitionQS(arr, low, high, pivotType);

        // Recurse into smaller half first (tail recursion optimization)
        if (pi - low < high - pi) {
            quickSort(arr, low, pi - 1, pivotType);
            low = pi + 1; // tail call for right half
        } else {
            quickSort(arr, pi + 1, high, pivotType);
            high = pi - 1; // tail call for left half
        }
    }
}

int main() {
    srand(time(0));
    vector<int> sizes = {10000, 50000, 100000};
    vector<string> patterns = {"ascending", "descending", "random"};
    vector<string> pivots = {"first", "last", "random", "median"};

    for (string pivotType : pivots) {
        cout << "\n=== Quick Sort (" << pivotType << " pivot) ===\n";
        for (int size : sizes) {
            cout << "\nSorting " << size << " elements\n";
            for (string pattern : patterns) {
                vector<int> arr = generateInput(size, pattern);
                clock_t start = clock();
                quickSort(arr, 0, arr.size() - 1, pivotType);
                clock_t end = clock();
                double time_taken = double(end - start) / CLOCKS_PER_SEC;
                cout << pattern << ": " << time_taken << " seconds\n";
            }
        }
    }
    return 0;
}
