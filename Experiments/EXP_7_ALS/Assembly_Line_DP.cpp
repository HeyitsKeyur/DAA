#include <bits/stdc++.h>
using namespace std;

#define NUM_LINES 2
#define NUM_STATIONS 4

int calculateAssemblyTime(int stationTime[][NUM_STATIONS],
                          int transferTime[][NUM_STATIONS],
                          int entryTime[], int exitTime[]) {
    int timeLineA[NUM_STATIONS];
    int timeLineB[NUM_STATIONS];
    int pathA[NUM_STATIONS];
    int pathB[NUM_STATIONS];

    // Base case
    timeLineA[0] = entryTime[0] + stationTime[0][0];
    timeLineB[0] = entryTime[1] + stationTime[1][0];
    pathA[0] = 0;
    pathB[0] = 1;

    // DP calculation
    for (int i = 1; i < NUM_STATIONS; ++i) {
        // Line A
        if (timeLineA[i - 1] <= timeLineB[i - 1] + transferTime[1][i]) {
            timeLineA[i] = timeLineA[i - 1] + stationTime[0][i];
            pathA[i] = 0;
        } else {
            timeLineA[i] = timeLineB[i - 1] + transferTime[1][i] + stationTime[0][i];
            pathA[i] = 1;
        }

        // Line B
        if (timeLineB[i - 1] <= timeLineA[i - 1] + transferTime[0][i]) {
            timeLineB[i] = timeLineB[i - 1] + stationTime[1][i];
            pathB[i] = 1;
        } else {
            timeLineB[i] = timeLineA[i - 1] + transferTime[0][i] + stationTime[1][i];
            pathB[i] = 0;
        }
    }

    // Compute final time
    int finalTime, finalLine;
    if (timeLineA[NUM_STATIONS - 1] + exitTime[0] <=
        timeLineB[NUM_STATIONS - 1] + exitTime[1]) {
        finalTime = timeLineA[NUM_STATIONS - 1] + exitTime[0];
        finalLine = 0;
    } else {
        finalTime = timeLineB[NUM_STATIONS - 1] + exitTime[1];
        finalLine = 1;
    }

    // Print formatted DP Table
    cout << "\nAssembly Line Scheduling DP Table\n";
    cout << "--------------------------------------------\n";
    cout << "                     ";
    for (int i = 0; i < NUM_STATIONS; ++i)
        cout << setw(8) << (i + 1);
    cout << "\n--------------------------------------------\n";

    cout << "f1/l1";
    for (int i = 0; i < NUM_STATIONS; ++i)
        cout << setw(10) << timeLineA[i] << "[" << pathA[i] + 1 << "]";
    cout << "\n";

    cout << "f2/l2";
    for (int i = 0; i < NUM_STATIONS; ++i)
        cout << setw(10) << timeLineB[i] << "[" << pathB[i] + 1 << "]";
    cout << "\n--------------------------------------------\n";

    // Trace final path
    vector<int> linePath(NUM_STATIONS);
    int line = finalLine;
    for (int i = NUM_STATIONS - 1; i >= 0; --i) {
        linePath[i] = line;
        if (line == 0)
            line = pathA[i];
        else
            line = pathB[i];
    }

    // Print path
    cout << "\nSelected Line Path:\n";
    for (int i = 0; i < NUM_STATIONS; ++i) {
        cout << "Station " << (i + 1) << " -> Line " << (linePath[i] + 1) << "\n";
    }

    // Print final result at the end
    cout << "Minimum Assembly Time:  " << finalTime << endl;

    return finalTime;
}

int main() {
    int stationTime[NUM_LINES][NUM_STATIONS] = {
        {4, 5, 3, 2},   // Line 1
        {2, 10, 1, 4}   // Line 2
    };

    int transferTime[NUM_LINES][NUM_STATIONS] = {
        {0, 7, 4, 5},   // From Line 1 → Line 2
        {0, 9, 2, 8}    // From Line 2 → Line 1
    };

    int entryTime[NUM_LINES] = {10, 12};
    int exitTime[NUM_LINES]  = {18, 7};

    calculateAssemblyTime(stationTime, transferTime, entryTime, exitTime);
    return 0;
}