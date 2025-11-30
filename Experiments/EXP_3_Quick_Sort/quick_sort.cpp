#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <string>
#include <map>
#include <numeric>

class QuickSortAnalyzer {
private:
    long long comparison_count;
    long long swap_count;

public:
    QuickSortAnalyzer() : comparison_count(0), swap_count(0) {
        srand(time(NULL)); // Seed the random number generator
    }
    
    void resetCounters() {
        comparison_count = 0;
        swap_count = 0;
    }
    
    long long getComparisons() const { return comparison_count; }
    long long getSwaps() const { return swap_count; }
    
    // Quick Sort with First Element as Pivot
    void quickSortFirst(std::vector<int>& arr, int low, int high) {
        if (low < high) {
            int pi = partitionFirst(arr, low, high);
            quickSortFirst(arr, low, pi - 1);
            quickSortFirst(arr, pi + 1, high);
        }
    }
    
    int partitionFirst(std::vector<int>& arr, int low, int high) {
        int pivot = arr[low];
        int i = low + 1;
        int j = high;
        
        while (true) {
            while (i <= j && ++comparison_count && arr[i] <= pivot) {
                i++;
            }
            
            while (i <= j && ++comparison_count && arr[j] >= pivot) {
                j--;
            }
            
            if (i >= j) break;
            
            std::swap(arr[i], arr[j]);
            swap_count++;
        }
        
        std::swap(arr[low], arr[j]);
        swap_count++;
        return j;
    }
    
    // Quick Sort with Last Element as Pivot
    void quickSortLast(std::vector<int>& arr, int low, int high) {
        if (low < high) {
            int pi = partitionLast(arr, low, high);
            quickSortLast(arr, low, pi - 1);
            quickSortLast(arr, pi + 1, high);
        }
    }
    
    int partitionLast(std::vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            comparison_count++;
            if (arr[j] <= pivot) {
                i++;
                if (i != j) {
                    std::swap(arr[i], arr[j]);
                    swap_count++;
                }
            }
        }
        
        std::swap(arr[i + 1], arr[high]);
        swap_count++;
        return i + 1;
    }
    
    // Quick Sort with Random Element as Pivot
    void quickSortRandom(std::vector<int>& arr, int low, int high) {
        if (low < high) {
            // Choose random pivot and swap with last element
            int randomIndex = low + rand() % (high - low + 1);
            std::swap(arr[randomIndex], arr[high]);
            swap_count++;
            
            int pi = partitionLast(arr, low, high);
            quickSortRandom(arr, low, pi - 1);
            quickSortRandom(arr, pi + 1, high);
        }
    }
    
    // Quick Sort with Median-of-Three as Pivot
    void quickSortMedian(std::vector<int>& arr, int low, int high) {
        if (low < high) {
            // Find median of three and swap with last element
            int mid = low + (high - low) / 2;
            int medianIndex = medianOfThree(arr, low, mid, high);
            std::swap(arr[medianIndex], arr[high]);
            swap_count++;
            
            int pi = partitionLast(arr, low, high);
            quickSortMedian(arr, low, pi - 1);
            quickSortMedian(arr, pi + 1, high);
        }
    }
    
    int medianOfThree(std::vector<int>& arr, int low, int mid, int high) {
        comparison_count += 2; // We make 2 comparisons to find median
        
        if ((arr[low] <= arr[mid] && arr[mid] <= arr[high]) || 
            (arr[high] <= arr[mid] && arr[mid] <= arr[low])) {
            return mid;
        } else if ((arr[mid] <= arr[low] && arr[low] <= arr[high]) || 
                   (arr[high] <= arr[low] && arr[low] <= arr[mid])) {
            return low;
        } else {
            return high;
        }
    }
    
    // Data Generation Functions
    std::vector<int> generateRandomData(int size) {
        std::vector<int> arr(size);
        for (int i = 0; i < size; i++) {
            arr[i] = rand() % (size * 10) + 1;
        }
        return arr;
    }
    
    std::vector<int> generateSortedData(int size) {
        std::vector<int> arr(size);
        std::iota(arr.begin(), arr.end(), 1);
        return arr;
    }
    
    std::vector<int> generateReverseSortedData(int size) {
        std::vector<int> arr(size);
        for (int i = 0; i < size; i++) {
            arr[i] = size - i;
        }
        return arr;
    }
    
    std::vector<int> generateNearlySortedData(int size) {
        std::vector<int> arr = generateSortedData(size);
        int numSwaps = std::max(1, size / 20); // Swap 5% of elements
        
        for (int i = 0; i < numSwaps; i++) {
            int idx1 = rand() % size;
            int idx2 = rand() % size;
            std::swap(arr[idx1], arr[idx2]);
        }
        return arr;
    }
    
    std::vector<int> generateDuplicateData(int size) {
        std::vector<int> uniqueValues;
        int numUnique = std::max(1, size / 10);
        
        for (int i = 0; i < numUnique; i++) {
            uniqueValues.push_back(rand() % (size / 10) + 1);
        }
        
        std::vector<int> arr(size);
        for (int i = 0; i < size; i++) {
            arr[i] = uniqueValues[rand() % numUnique];
        }
        return arr;
    }
    
    std::vector<int> generateData(const std::string& type, int size) {
        if (type == "random") return generateRandomData(size);
        else if (type == "sorted") return generateSortedData(size);
        else if (type == "reverse_sorted") return generateReverseSortedData(size);
        else if (type == "nearly_sorted") return generateNearlySortedData(size);
        else if (type == "duplicates") return generateDuplicateData(size);
        else return generateRandomData(size);
    }
    
    struct TestResult {
        double time;
        long long comparisons;
        long long swaps;
        bool success;
        
        TestResult() : time(0), comparisons(0), swaps(0), success(false) {}
        TestResult(double t, long long c, long long s) : time(t), comparisons(c), swaps(s), success(true) {}
    };
    
    TestResult testSortMethod(void (QuickSortAnalyzer::*sortMethod)(std::vector<int>&, int, int),
                             std::vector<int>& data) {
        resetCounters();
        
        clock_t start = clock();
        (this->*sortMethod)(data, 0, data.size() - 1);
        clock_t end = clock();
        
        double timeInSeconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;
        
        return TestResult(timeInSeconds, comparison_count, swap_count);
    }
    
    void runExperiment() {
        std::vector<int> sizes = {10000, 50000, 100000};
        std::vector<std::string> dataTypes = {"random", "sorted", "reverse_sorted", "nearly_sorted", "duplicates"};
        std::vector<std::string> methodNames = {"First Pivot", "Last Pivot", "Random Pivot", "Median Pivot"};
        
        // Method pointers
        std::vector<void (QuickSortAnalyzer::*)(std::vector<int>&, int, int)> methods = {
            &QuickSortAnalyzer::quickSortFirst,
            &QuickSortAnalyzer::quickSortLast,
            &QuickSortAnalyzer::quickSortRandom,
            &QuickSortAnalyzer::quickSortMedian
        };
        
        const int trials = 3;
        
        std::cout << "Quick Sort Pivot Selection Analysis" << std::endl;
        std::cout << "Testing different pivot selection strategies\n" << std::endl;
        
        std::cout << "Test Configuration:" << std::endl;
        std::cout << "- Input sizes: ";
        for (size_t i = 0; i < sizes.size(); i++) {
            std::cout << sizes[i];
            if (i < sizes.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
        std::cout << "- Data types: random, sorted, reverse_sorted, nearly_sorted, duplicates" << std::endl;
        std::cout << "- Trials per test: " << trials << std::endl;
        std::cout << "- Pivot strategies: First, Last, Random, Median-of-three\n" << std::endl;
        
        // Store results for analysis
        std::map<int, std::map<std::string, std::map<std::string, TestResult>>> results;
        
        for (int size : sizes) {
            std::cout << std::string(60, '=') << std::endl;
            std::cout << "Testing with input size: " << size << std::endl;
            std::cout << std::string(60, '=') << std::endl;
            
            for (const std::string& dataType : dataTypes) {
                std::cout << "\nData Type: " << dataType << std::endl;
                std::cout << std::string(40, '-') << std::endl;
                
                for (size_t methodIdx = 0; methodIdx < methods.size(); methodIdx++) {
                    std::vector<double> times;
                    std::vector<long long> comparisons;
                    std::vector<long long> swaps;
                    bool allSuccessful = true;
                    
                    for (int trial = 0; trial < trials; trial++) {
                        std::vector<int> testData = generateData(dataType, size);
                        
                        try {
                            TestResult result = testSortMethod(methods[methodIdx], testData);
                            
                            if (result.success) {
                                times.push_back(result.time);
                                comparisons.push_back(result.comparisons);
                                swaps.push_back(result.swaps);
                            } else {
                                allSuccessful = false;
                                break;
                            }
                        } catch (...) {
                            allSuccessful = false;
                            break;
                        }
                    }
                    
                    if (allSuccessful && !times.empty()) {
                        double avgTime = std::accumulate(times.begin(), times.end(), 0.0) / times.size();
                        double avgComparisons = std::accumulate(comparisons.begin(), comparisons.end(), 0LL) / static_cast<double>(comparisons.size());
                        double avgSwaps = std::accumulate(swaps.begin(), swaps.end(), 0LL) / static_cast<double>(swaps.size());
                        
                        results[size][dataType][methodNames[methodIdx]] = TestResult(avgTime, static_cast<long long>(avgComparisons), static_cast<long long>(avgSwaps));
                        
                        std::cout << "  " << std::setw(15) << std::left << methodNames[methodIdx] << ": "
                                  << std::fixed << std::setprecision(6) << avgTime << "s, "
                                  << static_cast<long long>(avgComparisons) << " comparisons, "
                                  << static_cast<long long>(avgSwaps) << " swaps" << std::endl;
                    } else {
                        std::cout << "  " << std::setw(15) << std::left << methodNames[methodIdx] << ": FAILED" << std::endl;
                        results[size][dataType][methodNames[methodIdx]] = TestResult();
                    }
                }
            }
        }
        
        // Analysis
        analyzeResults(results, sizes, dataTypes, methodNames);
    }
    
    void analyzeResults(const std::map<int, std::map<std::string, std::map<std::string, TestResult>>>& results,
                       const std::vector<int>& sizes, const std::vector<std::string>& dataTypes,
                       const std::vector<std::string>& methodNames) {
        
        std::cout << "\n" << std::string(80, '=') << std::endl;
        std::cout << "ANALYSIS AND OBSERVATIONS" << std::endl;
        std::cout << std::string(80, '=') << std::endl;
        
        // Best performance analysis
        for (int size : sizes) {
            std::cout << "\nSize " << size << " - Best Performance Summary:" << std::endl;
            std::cout << std::string(50, '-') << std::endl;
            
            for (const std::string& dataType : dataTypes) {
                double bestTime = 999999.0; // Large initial value
                std::string bestMethod = "";
                
                for (const std::string& method : methodNames) {
                    if (results.at(size).at(dataType).at(method).success) {
                        double time = results.at(size).at(dataType).at(method).time;
                        if (time < bestTime) {
                            bestTime = time;
                            bestMethod = method;
                        }
                    }
                }
                
                std::cout << "  " << std::setw(20) << std::left << dataType << ": " << bestMethod << std::endl;
            }
        }
        
        // Observations
        std::cout << "\n" << std::string(80, '=') << std::endl;
        std::cout << "KEY OBSERVATIONS:" << std::endl;
        std::cout << std::string(80, '=') << std::endl;
        
        std::vector<std::string> observations = {
            "1. FIRST PIVOT PERFORMANCE:",
            "   - Poor on sorted/reverse sorted data (O(n²) worst case)",
            "   - Good on random data",
            "   - Simple implementation, lowest overhead",
            "",
            "2. LAST PIVOT PERFORMANCE:",
            "   - Similar to first pivot but may behave differently on pre-sorted data",
            "   - Performance depends on data distribution",
            "",
            "3. RANDOM PIVOT PERFORMANCE:",
            "   - Most consistent across different data types",
            "   - Probabilistically avoids worst-case O(n²) behavior",
            "   - Slight overhead from random number generation",
            "",
            "4. MEDIAN PIVOT PERFORMANCE:",
            "   - Best theoretical performance (closest to balanced partitions)",
            "   - Higher overhead from median-of-three calculation",
            "   - Most stable performance across all data types",
            "",
            "5. GENERAL TRENDS:",
            "   - Random and median pivots are more robust",
            "   - First/last pivots vulnerable to adversarial input",
            "   - Performance differences more pronounced with larger datasets",
            "   - Nearly sorted data often shows interesting patterns"
        };
        
        for (const std::string& observation : observations) {
            std::cout << observation << std::endl;
        }
        
        std::cout << "\n" << std::string(80, '=') << std::endl;
        std::cout << "EXPERIMENT COMPLETED" << std::endl;
        std::cout << std::string(80, '=') << std::endl;
    }
};

int main() {
    QuickSortAnalyzer analyzer;
    analyzer.runExperiment();
    return 0;
}