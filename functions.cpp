#include <iostream>
#include <vector>
#include <algorithm>
#include "functions.h"

using namespace std;


int bruteForce(const vector<item>& items, int capacity) {
    int n = items.size();
    if(n>31) {
        cout << "The number of pallets is too high for brute-force approach.\n";
        return 0;
    }
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
        // Check for equal profit but better weight
        else if (current_weight <= capacity && current_profit == max_profit) {
            if (current_weight < best_weight) {
                best_weight = current_weight;
                best_subset = current_subset;
            }
            //Check for equal weight but less pallets used
            else if (current_weight == best_weight) {
                int counter1=0;
                int counter2=0;
                bool val=false;
                for (int j = 0; j < n; j++) {
                    if (current_subset[j] == true) {
                        counter1++;
                    }
                    if(best_subset[j] == true) {
                        counter2++;
                    }
                    if(counter1 > counter2) {
                        val=true;
                        
                    }
                }
                if (counter1 < counter2) {
                    best_weight = current_weight;
                    best_subset = current_subset;
                }
                //Check for better id
                else if (counter1 == counter2)  {
                    if(val==true){
                        best_weight = current_weight;
                        best_subset = current_subset;
                    }
                }
            }
        }
    }

    cout << "\nOptimal Solution Found:\n";
    cout << "Weight Used: " << best_weight << " of " << capacity << "\n";
    cout << "Profit Obtained: " << max_profit << "\n";
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (best_subset[i]) {
            count++;
        }
    }
    
    cout << "Used " << count << " of " << n << " pallets:\n";
    
    for (int i = 0; i < n; i++) {
        if (best_subset[i]) {
            cout << "Pallet n "<<i+1 << " : Weight= " << items[i].weight 
                 << " /Profit= " << items[i].profit << "\n";
        }
    }
    return max_profit;
}

int approximation(vector<item> values, int capacity){
    int W = 0, no_more = 0,index = 0, V = 0, sum = 0;
    int n = values.size();
    vector<int> usedPallets;
    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;
    sort(order.begin(), order.end(), [&](int a, int b) {
        return cmp(a, b, values);
    });
    cout << "\n=== Greedy Approach ===\n";
    cout << "Total Pallets: " << n << "\n";
    while(W != capacity && no_more != 1){
        int pos = order[index];
        if(W + values[pos].weight <= capacity){
            W = W + values[pos].weight;
            V = V + values[pos].profit;
            sum ++;
            usedPallets.push_back(pos);
        }else{
            no_more = 1;
        }
        index++;
    }
    sort(usedPallets.begin(), usedPallets.end());
    cout << "\nWeight Used: " << W << " of " << capacity << endl;
    cout << "Profit Obtained: " << V << endl;
    cout << "Used "<<sum<<" of "<<n<<" Pallets!"<<endl;
    for(size_t i = 0; i < usedPallets.size(); ++i){
        int id = usedPallets[i];
        cout << "Pallet " << id + 1
            << " : Weight= " << values[id].weight
            << " /Profit= " << values[id].profit << endl;
    }
    return V;
}

int dynamicProgramming(vector<item>& values, int capacity) {
    int n = values.size();
    vector<vector<State>> dp(n+1, vector<State>(capacity+1));

    for (int i = 0; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            dp[i][w] = {0, 0, {}};
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            State without = dp[i-1][w];
            State with = {0, 0, {}};

            if (values[i-1].weight <= w) {
                State prev = dp[i-1][w - values[i-1].weight];
                with.profit = prev.profit + values[i-1].profit;
                with.weight = prev.weight + values[i-1].weight;
                with.pallets = prev.pallets;
                with.pallets.push_back(i-1);
            }

            dp[i][w] = max(without, with);
        }
    }

    State best = dp[n][capacity];

    cout << "\nOptimal Solution Found:\n";
    cout << "Weight Used: " << best.weight << " of " << capacity << endl;
    cout << "Profit Obtained: " << best.profit << endl;
    cout << "Used " << best.pallets.size() << " of " << n << " Pallets!\n";

    sort(best.pallets.begin(), best.pallets.end());

    for (int id : best.pallets) {
        cout << "Pallet " << id+1 << " : Weight= " << values[id].weight
             
        << " /Profit= " << values[id].profit << endl;
    }
    return best.profit;
}

int ilpAlgorithm(vector<item>& values, int capacity) {
    int n = values.size();
    cout << "\n=== Integer Linear Programming Algorithm ===\n";
    cout << "Total Pallets: " << n << "\n";

    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;

    sort(order.begin(), order.end(), [&](int a, int b) {
        return cmp(a, b, values);
    });

    int maxProfit = 0;
    int minWeight = capacity + 1;
    vector<int> currentSelection;
    vector<int> bestSelection;

    truck(0, n, 0, 0, capacity, order, values, maxProfit, minWeight, currentSelection, bestSelection);

    int totalWeight = 0;
    cout << "\nOptimal Solution Found:\n";
    for (int idx : bestSelection) totalWeight += values[idx].weight;
    cout << "Weight Used: " << totalWeight << " of " << capacity << endl;
    cout << "Profit Obtained: " << maxProfit << endl;
    cout << "Used " << bestSelection.size() << " of " << n << " Pallets!\n";

    vector<int> sortedBest = bestSelection;
    sort(sortedBest.begin(), sortedBest.end());
    for (int idx : sortedBest) {
        cout << "Pallet " << idx + 1 << " : Weight= " << values[idx].weight
             << " /Profit= " << values[idx].profit << endl;
    }
    return maxProfit;
}

bool cmp(int a, int b, const vector<item>& items) {
    double r1 = (double)items[a].profit / items[a].weight;
    double r2 = (double)items[b].profit / items[b].weight;
    if (r1 != r2) return r1 > r2;
    return a < b;
}

double bound(int idx, int n, int currWeight, int currProfit, int W, const vector<int>& order, const vector<item>& items) {
    if (currWeight >= W) return currProfit;
    double result = currProfit;
    int totalWeight = currWeight;
    for (int i = idx; i < n; i++) {
        int itemIdx = order[i];
        if (totalWeight + items[itemIdx].weight <= W) {
            totalWeight += items[itemIdx].weight;
            result += items[itemIdx].profit;
        } else {
            int remain = W - totalWeight;
            result += (double)items[itemIdx].profit / items[itemIdx].weight * remain;
            break;
        }
    }
    return result;
}

void truck(int idx, int n, int currWeight, int currProfit, int W, const vector<int>& order, const vector<item>& items,
           int& maxProfit, int& minWeight, vector<int>& currentSelection, vector<int>& bestSelection) {

    if (currWeight > W) return;

    if (idx == n) {
        if (currProfit > maxProfit ||
            (currProfit == maxProfit && (currWeight < minWeight ||
            (currWeight == minWeight && (currentSelection.size() < bestSelection.size() ||
            (currentSelection.size() == bestSelection.size() && isBetterSelection(currentSelection, bestSelection))))))) {
            
            maxProfit = currProfit;
            minWeight = currWeight;
            bestSelection = currentSelection;
        }
        return;
    }

    double B = bound(idx, n, currWeight, currProfit, W, order, items);

    if (B < maxProfit) return;

    int itemIdx = order[idx];

    currentSelection.push_back(itemIdx);
    truck(idx + 1, n, currWeight + items[itemIdx].weight, currProfit + items[itemIdx].profit,
          W, order, items, maxProfit, minWeight, currentSelection, bestSelection);
    currentSelection.pop_back();

    truck(idx + 1, n, currWeight, currProfit,
          W, order, items, maxProfit, minWeight, currentSelection, bestSelection);
}

bool isBetterSelection(const vector<int>& a, const vector<int>& b) {
    vector<int> sortedA = a;
    vector<int> sortedB = b;
    sort(sortedA.begin(), sortedA.end());
    sort(sortedB.begin(), sortedB.end());
    return sortedA < sortedB;
}

void backtrackingRecursion(size_t i, int current_weight, int current_profit,const vector<item>& items, int capacity,
            int& max_profit, int& best_weight,vector<bool>& current_subset, vector<bool>& best_subset,int& nodes_visited) {
    
    if (current_weight > capacity) {
        return;
    }
    
    nodes_visited++;
    if (i == items.size()) {
        if (current_weight <= capacity && current_profit > max_profit) {
            max_profit = current_profit;
            best_weight = current_weight;
            best_subset = current_subset;
        }
        else if (current_weight <= capacity && current_profit == max_profit) {
            if (current_weight < best_weight) {
                best_weight = current_weight;
                best_subset = current_subset;
            }
            else if (current_weight == best_weight) {
                int counter1=0;
                int counter2=0;
                bool val=false;
                for (size_t j = 0; j < items.size(); j++) {
                    if (current_subset[j] == true) {
                        counter1++;
                    }
                    if(best_subset[j] == true) {
                        counter2++;
                    }
                    if(counter1 > counter2) {
                        val=true;
                        
                    }
                }
                if (counter1 < counter2) {
                    best_weight = current_weight;
                    best_subset = current_subset;
                }
                else if (counter1 == counter2)  {
                    if(val==true){
                        best_weight = current_weight;
                        best_subset = current_subset;
                    }
                }
            }
        }
        return;
    }

    int remaining_profit = 0;
    for (size_t j = i; j < items.size(); j++) {
        remaining_profit += items[j].profit;
    }
    if (current_profit + remaining_profit <= max_profit) {
        return;
    }

    current_subset[i] = false;
    backtrackingRecursion(i+1, current_weight, current_profit,items, capacity, max_profit, best_weight,current_subset, best_subset,nodes_visited);

    if (current_weight + items[i].weight <= capacity) {
        current_subset[i] = true;
        backtrackingRecursion(i+1, current_weight + items[i].weight,current_profit + items[i].profit,items, capacity,max_profit, best_weight,current_subset, best_subset,nodes_visited);
    }
}

int backtracking(const vector<item>& items, int capacity) {
    int n = items.size();
    int max_profit = 0;
    int best_weight = 0;
    vector<bool> best_subset(n, false);
    vector<bool> current_subset(n, false);
    int nodes_visited = 0;

    cout << "\n=== Backtracking Approach ===\n";

    backtrackingRecursion(0, 0, 0,items, capacity,max_profit, best_weight,current_subset, best_subset,nodes_visited);


    cout << "\nOptimal Solution Found:\n";
    if(items.size() > 31) {
        cout << "Nodes visited: " << nodes_visited << " (vs not calculated in brute-force)\n";
    }
    else cout << "Nodes visited: " << nodes_visited << " (vs " << (1 << n) << " in brute-force)\n";
    cout << "Weight Used: " << best_weight << " of " << capacity << "\n";
    cout << "Profit Obtained: " << max_profit << "\n";
    cout << "Pallets Used: ";
    
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (best_subset[i]) {
            count++;
        }
    }
    
    cout << "Used " << count << " of " << n << " pallets:\n";
    
    for (int i = 0; i < n; i++) {
        if (best_subset[i]) {
            cout << "Pallet n " << i+1 << " : Weight= " << items[i].weight 
                 << " /Profit= " << items[i].profit << "\n";
        }
    }
    return max_profit;
}