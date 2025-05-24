#ifndef FUNCTIONS
#define FUNCTIONS

using namespace std;

struct item{
    int weight;
    int profit;
};
struct State {
    int profit;
    int weight;
    vector<int> pallets;

    bool operator<(const State& other) const {
        if (profit != other.profit)
            return profit < other.profit;
        if (weight != other.weight)
            return weight > other.weight;
        if (pallets.size() != other.pallets.size())
            return pallets.size() > other.pallets.size();
        return pallets > other.pallets;
    }
};
void bruteForce(const vector<item>& items, int capacity);
void approximation(vector<item> values, int capacity);
void dynamicProgramming(vector<item>& values, int capacity);
void ilpAlgorithm(vector<item>& values, int capacity);
bool cmp(int a, int b, const vector<item>& items);
double bound(int idx, int n, int currWeight, int currProfit, int W, const vector<int>& order, const vector<item>& items);
void truck(int idx, int n, int currWeight, int currProfit, int W, const vector<int>& order, const vector<item>& items,
           int& maxProfit, int& minWeight, vector<int>& currentSelection, vector<int>& bestSelection);
void backtrackingRecursion(size_t i, int current_weight, int current_profit,const vector<item>& items, int capacity,
              int& max_profit, int& best_weight,vector<bool>& current_subset, vector<bool>& best_subset,int& nodes_visited);
void backtracking(const vector<item>& items, int capacity);
bool isBetterSelection(const vector<int>& a, const vector<int>& b);

#endif