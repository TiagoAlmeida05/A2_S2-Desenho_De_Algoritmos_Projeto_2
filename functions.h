/**
 * @file functions.h
 * @brief Header file containing knapsack-related function declarations and data structures.
 */

#ifndef FUNCTIONS
#define FUNCTIONS

using namespace std;

/**
 * @brief Represents a pallet with weight and profit.
 */
struct item {
    int weight;  /**< Weight of the pallet */
    int profit;  /**< Profit value of the pallet */
};

/**
 * @brief Represents a state used in dynamic programming solution.
 * 
 * Stores the total profit, total weight, and the indices of pallets selected.
 */
struct State {
    int profit;            /**< Total profit of selected pallets */
    int weight;            /**< Total weight of selected pallets */
    std::vector<int> pallets; /**< Indices of pallets included in this state */

    /**
     * @brief Comparison operator to compare two states.
     * 
     * States are compared by:
     * 1. Profit (higher is better)
     * 2. Weight (lower is better)
     * 3. Number of pallets used (lower is better)
     * 4. Lexicographical order of pallet indices
     * 
     * @param other Another state to compare with
     * @return true if this state is "less" than other, false otherwise
     */
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
/**
 * @brief Solves pallet packing using brute-force approach.
 * 
 * Enumerates all subsets of pallets to find the optimal profit without exceeding capacity.
 * Limits input size to 31 pallets to avoid excessive computation.
 * 
 * @param items Vector of pallets (weight and profit).
 * @param capacity Maximum weight capacity of the truck.
 * @return int Maximum profit achievable.
 */
int bruteForce(const vector<item>& items, int capacity);

/**
 * @brief Approximates solution using a greedy approach based on profit-to-weight ratio.
 * 
 * Sorts pallets by descending ratio and picks greedily until capacity is reached.
 * 
 * @param values Vector of pallets.
 * @param capacity Maximum capacity.
 * @return int Approximate profit.
 */
int approximation(vector<item> values, int capacity);

/**
 * @brief Uses dynamic programming to find optimal packing.
 * 
 * Constructs a DP table with States storing profit, weight, and pallets used.
 * 
 * @param values Vector of pallets.
 * @param capacity Maximum capacity.
 * @return int Optimal profit.
 */
int dynamicProgramming(vector<item>& values, int capacity);

/**
 * @brief Solves pallet packing via Integer Linear Programming with branch and bound.
 * 
 * Uses recursive search with bounding to prune suboptimal branches.
 * 
 * @param values Vector of pallets.
 * @param capacity Maximum capacity.
 * @return int Optimal profit.
 */
int ilpAlgorithm(vector<item>& values, int capacity);

/**
 * @brief Comparator for sorting pallets by profit-to-weight ratio.
 * 
 * @param a Index of first pallet.
 * @param b Index of second pallet.
 * @param items Vector of pallets.
 * @return true if pallet a has higher ratio or if equal, smaller index.
 */
bool cmp(int a, int b, const vector<item>& items);

/**
 * @brief Calculates upper bound on profit for branch and bound.
 * 
 * Uses fractional knapsack idea to estimate max profit from current index.
 * 
 * @param idx Current index in ordered pallets.
 * @param n Total number of pallets.
 * @param currWeight Current total weight.
 * @param currProfit Current total profit.
 * @param W Maximum capacity.
 * @param order Ordering of pallets.
 * @param items Vector of pallets.
 * @return double Upper bound estimate of profit.
 */
double bound(int idx, int n, int currWeight, int currProfit, int W, const vector<int>& order, const vector<item>& items);

/**
 * @brief Recursive helper for ILP branch and bound search.
 * 
 * @param idx Current index in pallets.
 * @param n Total pallets count.
 * @param currWeight Current weight.
 * @param currProfit Current profit.
 * @param W Maximum capacity.
 * @param order Sorted order of pallets.
 * @param items Vector of pallets.
 * @param maxProfit Reference to max profit found.
 * @param minWeight Reference to minimum weight for max profit.
 * @param currentSelection Current pallets selected.
 * @param bestSelection Best pallets selected.
 */
void truck(int idx, int n, int currWeight, int currProfit, int W, const vector<int>& order, const vector<item>& items,
           int& maxProfit, int& minWeight, vector<int>& currentSelection, vector<int>& bestSelection);

/**
 * @brief Compares two selections of pallets to determine which is lexicographically better.
 * 
 * @param a First selection.
 * @param b Second selection.
 * @return true if a is lexicographically less than b.
 */
bool isBetterSelection(const vector<int>& a, const vector<int>& b);

/**
 * @brief Recursive helper function for backtracking solution.
 * 
 * Explores subsets recursively with pruning to find optimal profit.
 * 
 * @param i Current pallet index.
 * @param current_weight Current total weight.
 * @param current_profit Current total profit.
 * @param items Vector of pallets.
 * @param capacity Maximum capacity.
 * @param max_profit Reference to max profit found.
 * @param best_weight Reference to best weight for max profit.
 * @param current_subset Current pallet selection.
 * @param best_subset Best pallet selection.
 * @param nodes_visited Counter for nodes visited during recursion.
 */
void backtrackingRecursion(size_t i, int current_weight, int current_profit,const vector<item>& items, int capacity,
            int& max_profit, int& best_weight,vector<bool>& current_subset, vector<bool>& best_subset,int& nodes_visited);

/**
 * @brief Solves pallet packing using backtracking with pruning.
 * 
 * Provides optimal solution by exploring subsets and pruning suboptimal branches.
 * 
 * @param items Vector of pallets.
 * @param capacity Maximum capacity.
 * @return int Maximum profit.
 */
int backtracking(const vector<item>& items, int capacity);
#endif