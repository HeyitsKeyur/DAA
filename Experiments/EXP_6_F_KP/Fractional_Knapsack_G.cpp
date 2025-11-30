#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    double profit;
    double weight;
};

bool ratioComparator(const Item &a, const Item &b) {
    return (a.profit / a.weight) > (b.profit / b.weight);
}

double knapsackFractional(int n, double capacity, vector<Item> items) {
    
    sort(items.begin(), items.end(), ratioComparator);

    double currentProfit = 0.0;
    double remainingCapacity = capacity;

    for (int i = 0; i < n; i++) {
        if (items[i].weight <= remainingCapacity) {
            currentProfit += items[i].profit;
            remainingCapacity -= items[i].weight;
        } else {
            double fraction = remainingCapacity / items[i].weight;
            currentProfit += items[i].profit * fraction;
            break; // Bag is full
        }
    }

    return currentProfit;
}

int main() {
    int n;
    double capacity;

    cout << "Enter total number of items: ";
    cin >> n;

    vector<Item> items(n);
    cout << "Enter profit and weight of items:\n";
    for (int i = 0; i < n; i++) {
        cin >> items[i].profit >> items[i].weight;
    }

    cout << "Enter capacity of knapsack: ";
    cin >> capacity;

    double result = knapsackFractional(n, capacity, items);

    cout << "\nThe maximum profit obtained = " << result << endl;

    return 0;
}
