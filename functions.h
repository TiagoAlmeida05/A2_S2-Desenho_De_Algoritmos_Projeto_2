#ifndef FUNCTIONS
#define FUNCTIONS

using namespace std;

struct item{
    int weight;
    int profit;
};
void bruteForce(const vector<item>& items, int capacity);
void approximation(vector<item> values, int capacity);
void dynamicProgramming(vector<item>& values, int capacity);

#endif