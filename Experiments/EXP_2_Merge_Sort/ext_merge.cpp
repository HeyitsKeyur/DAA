#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <climits>   // for INT_MAX
#include <cstdio>    // for remove()

using namespace std;

// Function to generate input data and store in file
void generateInputFile(string filename, int n, string type) {
    ofstream fout(filename);
    if (type == "ascending") {
        for (int i = 0; i < n; i++) fout << i << " ";
    } else if (type == "descending") {
        for (int i = n; i > 0; i--) fout << i << " ";
    } else if (type == "random") {
        for (int i = 0; i < n; i++) fout << rand() % n << " ";
    }
    fout.close();
}

// Phase 1: Break input file into sorted chunks
void createSortedChunks(string inputFile, int chunkSize, vector<string> &chunkFiles) {
    ifstream fin(inputFile);
    vector<int> buffer;
    buffer.reserve(chunkSize);

    int value, chunkCount = 0;
    while (fin >> value) {
        buffer.push_back(value);
        if (buffer.size() == chunkSize) {
            sort(buffer.begin(), buffer.end());
            string chunkName = "chunk_" + to_string(chunkCount++) + ".txt";
            ofstream fout(chunkName);
            for (int x : buffer) fout << x << " ";
            fout.close();
            chunkFiles.push_back(chunkName);
            buffer.clear();
        }
    }

    // leftover values
    if (!buffer.empty()) {
        sort(buffer.begin(), buffer.end());
        string chunkName = "chunk_" + to_string(chunkCount++) + ".txt";
        ofstream fout(chunkName);
        for (int x : buffer) fout << x << " ";
        fout.close();
        chunkFiles.push_back(chunkName);
    }
    fin.close();
}

// Phase 2: Merge sorted chunks into final output file
void mergeChunks(vector<string> &chunkFiles, string outputFile) {
    vector<ifstream> fins(chunkFiles.size());
    for (int i = 0; i < chunkFiles.size(); i++) {
        fins[i].open(chunkFiles[i]);
    }

    ofstream fout(outputFile);
    vector<int> current(chunkFiles.size());
    vector<char> available(chunkFiles.size(), 1);  // use char instead of bool

    // initialize
    for (int i = 0; i < chunkFiles.size(); i++) {
        if (!(fins[i] >> current[i])) {
            available[i] = 0;
        }
    }

    while (1) {   // or use for(;;)
        int minIndex = -1;
        int minValue = INT_MAX;

        for (int i = 0; i < chunkFiles.size(); i++) {
            if (available[i] && current[i] < minValue) {
                minValue = current[i];
                minIndex = i;
            }
        }

        if (minIndex == -1) break; // all exhausted

        fout << minValue << " ";
        if (!(fins[minIndex] >> current[minIndex])) {
            available[minIndex] = 0;
        }
    }

    fout.close();
    for (auto &f : fins) f.close();

    // cleanup chunk files
    for (string &f : chunkFiles) {
        remove(f.c_str());
    }
}

int main() {
    srand(time(0));
    vector<int> sizes = {10000, 50000, 100000};
    vector<string> patterns = {"ascending", "descending", "random"};

    int chunkSize = 5000; // memory capacity for each chunk

    cout << "\n=== External Merge Sort ===\n";

    for (int n : sizes) {
        cout << "\nSorting " << n << " elements\n";

        for (string pattern : patterns) {
            string inputFile = "input_" + to_string(n) + "_" + pattern + ".txt";
            string outputFile = "output_" + to_string(n) + "_" + pattern + ".txt";

            // generate input
            generateInputFile(inputFile, n, pattern);

            // phase 1: split into chunks
            vector<string> chunkFiles;
            createSortedChunks(inputFile, chunkSize, chunkFiles);

            // phase 2: merge chunks
            clock_t start = clock();
            mergeChunks(chunkFiles, outputFile);
            clock_t end = clock();

            double time_taken = double(end - start) / CLOCKS_PER_SEC;
            cout << pattern << ": " << time_taken << " seconds\n";
        }
    }

    return 0;
}