#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "functions.h"

using namespace std;

void displayMenu();

void loadTruck(int& capacity, int& pallets);

vector<item> loadPallets();


int main()
{        
    int capacity, pallets = 0; 
    vector <item> values;
    system("cls");
    char choice;
    do
    {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;



        switch (choice)
        {
        case '1':{
            loadTruck(capacity, pallets);
            values = loadPallets();
            break;            
        }
        case '2':
            bruteForce(values, capacity);
            break;
        case '3':
            bruteForce(values, capacity);
            break;
        case '4':
            dynamicProgramming(values, capacity);
            break;
        case '5':
            approximation(values, capacity);
            break;  
        case '6':
            ilpAlgorithm(values, capacity);
            break;            

        case '7':
            cout << "Exiting Program... \n";
            break;
        default:
            cout << "Invalid choice \n";
        }
    } while (choice != '7');

    return 0;
}

void displayMenu()
{
    cout << "\n=====  Pallet Packing Optimization Tool =====\n";
    cout << "1. Select Truck and Pallets\n";
    cout << "2. Exhaustive (Brute-Force) Approach\n";
    cout << "3. Backtracking Approach\n";
    cout << "4. Dynamic Programming Approach\n";
    cout << "5. Approximation Algorithms (Greedy Approach)\n";
    cout << "6. Integer Linear Programming Algorithm (ILP)\n";
    cout << "7. Exit\n";
}

void loadTruck(int& capacity, int& pallets)
{
    string filename;
    string line;

    cout << "Enter File Name With Truck:  \n";
    cin >> filename;

    ifstream inputfile1(filename);

    if (!inputfile1)
    {
        cout << "Error: Could not open " << filename << "!\n";
    }
    getline(inputfile1, line);
    while (getline(inputfile1, line))
    {
        stringstream ss(line);
        string capa, pall;

        getline(ss, capa, ',');
        getline(ss, pall, ',');

        capacity = stoi(capa);
        pallets = stoi(pall);
    }
}

vector<item> loadPallets()
{
    vector <item> values;
    item pallet;
    string filename;
    string line;

    cout << "Enter File Name with Pallets:  \n";
    cin >> filename;

    ifstream inputfile2(filename);

    if (!inputfile2)
    {
        cout << "Error: Could not open " << filename << "!\n";
    }
    getline(inputfile2, line);
    while (getline(inputfile2, line))
    {
        stringstream ss(line);
        string pall, wei, prof;
        getline(ss, pall, ',');
        getline(ss, wei, ',');
        getline(ss, prof, ',');
        pallet.weight = stoi(wei);
        pallet.profit = stoi(prof);
        values.push_back(pallet);
    }
    return values;
}

