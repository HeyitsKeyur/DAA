#include <iostream>
#include <vector>
#include <ctime> 

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

// Bubble Sort
void bubbleSort(vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                mySwap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// Selection Sort
void selectionSort(vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            mySwap(arr[i], arr[minIndex]);
        }
    }
}

// Insertion Sort
void insertionSort(vector<int> &arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Quick Sort
int partitionQS(vector<int> &arr, int low, int high) {
    // Use median-of-three pivot selection to avoid worst case
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid]) mySwap(arr[low], arr[mid]);
    if (arr[low] > arr[high]) mySwap(arr[low], arr[high]);
    if (arr[mid] > arr[high]) mySwap(arr[mid], arr[high]);
    
    // Place pivot at high-1
    mySwap(arr[mid], arr[high - 1]);
    int pivot = arr[high - 1];
    
    int i = low;
    int j = high - 1;
    
    while (true) {
        while (arr[++i] < pivot);
        while (arr[--j] > pivot);
        if (i < j) {
            mySwap(arr[i], arr[j]);
        } else {
            break;
        }
    }
    
    mySwap(arr[i], arr[high - 1]);
    return i;
}

void quickSort(vector<int> &arr, int low, int high) {
   
    if (high - low + 1 <= 10) {
        for (int i = low + 1; i <= high; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= low && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
        return;
    }
    
    if (low < high) {
        int pi = partitionQS(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    srand(time(0));
    vector<int> sizes = {10000, 50000, 100000};
    vector<string> patterns = {"ascending", "descending", "random"};

    // Bubble Sort section
    cout << "\n=== Bubble Sort ===\n";
    for (int size : sizes) {
        cout << "\nSorting " << size << " elements\n";
        for (string pattern : patterns) {
            vector<int> arr = generateInput(size, pattern);
            clock_t start = clock();
            bubbleSort(arr);
            clock_t end = clock();
            double time_taken = double(end - start) / CLOCKS_PER_SEC;
            cout << pattern << ": " << time_taken << " seconds\n";
        }
    }

    // Selection Sort section
    cout << "\n=== Selection Sort ===\n";
    for (int size : sizes) {
        cout << "\nSorting " << size << " elements\n";
        for (string pattern : patterns) {
            vector<int> arr = generateInput(size, pattern);
            clock_t start = clock();
            selectionSort(arr);
            clock_t end = clock();
            double time_taken = double(end - start) / CLOCKS_PER_SEC;
            cout << pattern << ": " << time_taken << " seconds\n";
        }
    }

    // Insertion Sort section
    cout << "\n=== Insertion Sort ===\n";
    for (int size : sizes) {
        cout << "\nSorting " << size << " elements\n";
        for (string pattern : patterns) {
            vector<int> arr = generateInput(size, pattern);
            clock_t start = clock();
            insertionSort(arr);
            clock_t end = clock();
            double time_taken = double(end - start) / CLOCKS_PER_SEC;
            cout << pattern << ": " << time_taken << " seconds\n";
        }
    }

    // Quick Sort section
    cout << "\n=== Quick Sort ===\n";
    for (int size : sizes) {
        cout << "\nSorting " << size << " elements\n";
        for (string pattern : patterns) {
            vector<int> arr = generateInput(size, pattern);
            clock_t start = clock();
            quickSort(arr, 0, arr.size() - 1);
            clock_t end = clock();
            double time_taken = double(end - start) / CLOCKS_PER_SEC;
            cout << pattern << ": " << time_taken << " seconds\n";
        }
    }

    return 0;
}
