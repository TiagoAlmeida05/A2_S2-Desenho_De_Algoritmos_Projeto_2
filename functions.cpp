#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "functions.h"

void bruteForce(const vector<item>& items, int capacity) {
    int n = items.size();
    int max_profit = 0;
    int best_weight = 0;
    vector<bool> best_subset(n, false);
    long total_subsets = 1 << n; // total subsets = 2^n

    cout << "\n=== Brute-Force Approach ===\n";
    cout << "Total pallets: " << n << "\n";
    cout << "Total possible subsets: " << total_subsets << "\n";

    for (long mask = 0; mask < total_subsets; mask++) {
        int current_weight = 0;
        int current_profit = 0;
        vector<bool> current_subset(n, false);

        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                current_weight += items[i].weight;
                current_profit += items[i].profit;
                current_subset[i] = true;
            }
        }

        if (current_weight <= capacity && current_profit > max_profit) {
            max_profit = current_profit;
            best_weight = current_weight;
            best_subset = current_subset;
        }
    }

    cout << "\nOptimal Solution Found:\n";
    cout << "Weight Used: " << best_weight << " of " << capacity << "\n";
    cout << "Profit Obtained: " << max_profit << "\n";
    cout << "Used " << best_subset.size()<<" of " << n << " pallets:\n";

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (best_subset[i]) {
            cout << "Pallet "<<i+1 << " : Weight= " << items[i].weight 
                 << " /Profit= " << items[i].profit << "\n";
            count++;
        }
    }
}

void approximation(vector<item> values, int capacity){
    int W = 0, no_more = 0, index = 0, V = 0, sum = 0;
    int n = values.size();
    vector<int> usedPallets;
    vector<int> profit;
    cout << "\n=== Greedy Approach ===\n";
    cout << "Total Pallets: " << n << "\n";
    while(W != capacity && no_more != 1){
        double br = 0;
        for(int i = 0; i < n; i++){
            item current = values[i];
            double ratio = static_cast<double>(current.profit)/current.weight;
            if(ratio > br){
                br = ratio;
                index = i;
            }
        }
        if(br == 0){
            no_more = 1;
        }else {
            if(W + values[index].weight <= capacity){
                W = W + values[index].weight;
                V = V + values[index].profit;
                profit.push_back(values[index].profit);
                values[index].profit = 0;
                sum ++;
                usedPallets.push_back(index);
            }else{
                values[index].profit = 0;
            }
        }

    }
    cout << "\nWeight Used: " << W << " of " << capacity << endl;
    cout << "Profit Obtained: " << V << endl;
    cout << "Used "<<sum<<" of "<<n<<" Pallets!"<<endl;
    for(size_t i = 0; i < usedPallets.size(); ++i){
        int id = usedPallets[i];
        cout << "Pallet " << id + 1
            << " : Weight= " << values[id].weight
            << " /Profit= " << profit[i] << endl;
    }
}

void dynamicProgramming(vector<item>& values, int capacity) {
    int n = values.size();
    vector<vector<int>> dp(n+1, vector<int>(capacity+1, 0));

    cout << "\n=== Dynamic Programming Approach ===\n";
    cout << "Total Pallets: " << n << "\n";

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            if (values[i-1].weight <= w) {
                dp[i][w] = max(
                    values[i-1].profit + dp[i-1][w - values[i-1].weight],
                    dp[i-1][w]
                );
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }

    int w = capacity;
    int totalWeight = 0;
    int totalProfit = 0;
    vector<int> usedPallets;
    vector<int> profitValues;

    for (int i = n; i >= 1; --i) {
        if (dp[i][w] != dp[i-1][w]) {
            usedPallets.push_back(i-1);
            profitValues.push_back(values[i-1].profit);
            totalWeight += values[i-1].weight;
            totalProfit += values[i-1].profit;
            w -= values[i-1].weight;
        }
    }
    cout << "\nOptimal Solution Found:\n";
    cout << "Weight Used: " << totalWeight << " of " << capacity << endl;
    cout << "Profit Obtained: " << totalProfit << endl;
    cout << "Used " << usedPallets.size() << " of " << n << " Pallets!" << endl;

    for (size_t i = 0; i < usedPallets.size(); ++i) {
        int id = usedPallets[i];
        cout << "Pallet " << id + 1
                  << " : Weight= " << values[id].weight
                  << " /Profit= " << profitValues[i] << endl;
    }
}