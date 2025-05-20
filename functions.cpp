#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "functions.h"

void approximation(vector<item> values, int capacity, int pallets){
    int W = 0, no_more = 0, index = 0, V = 0, sum = 0;
    vector<int> usedPallets;
    vector<int> profit;
    while(W != capacity && no_more != 1){
        double br = 0;
        for(int i = 0; i < pallets; i++){
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
    cout << "Weight Used: " << W << " of " << capacity << endl;
    cout << "Profit Obtained: " << V << endl;
    cout << "Used "<<sum<<" of "<<pallets<<" Pallets!"<<endl;
    for(size_t i = 0; i < usedPallets.size(); ++i){
        int id = usedPallets[i];
        cout << "Pallet n " << id 
            << " : Weight= " << values[id].weight 
            << " /Profit= " << profit[i] << endl;
    }

}