#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct item{
    int weight;
    int profit;
};

void displayMenu();

void loadTruck(int capacity, int pallets);

void loadPallets(vector<item> values);


int main()
{
    system("cls");
    char choice;
    do
    {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        int capacity, pallets = 0;


        switch (choice)
        {
        case '1':{
            loadTruck(capacity, pallets);
            vector <item> values(pallets);
            loadPallets(values);
            break;            
        }
        case '2':
            break;
        case '3':
            break;
        case '4':
            break;
        case '5':
            break;
        case '6':
            break;
        case '7':
            cout << "Exiting Program... \n";
            break;
        default:
            cout << "Invalid choice \n";
        }
    } while (choice != '4');

    return 0;
}

void displayMenu()
{
    cout << "\n=====  Pallet Packing Optimization Tool =====\n";
    cout << "1. Load Trucks and Pallets from File\n";
    cout << "2. Exhaustive (Brute-Force) Approach\n";
    cout << "3. Dynamic Programming Approach\n";
    cout << "5. Approximation Algorithms (Greedy Approach)\n";
    cout << "6. Integer Linear Programming Algorithm (ILP)\n";
    cout << "7. Exit\n";
}

void loadTruck(int capacity, int pallets)
{
    string filename;
    string line;

    cout << "Enter File Name With Trunk:  \n";
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

void loadPallets(vector<item> values)
{
    item pallet;
    string filename;
    string line;

    cout << "Enter File Name Pallets:  \n";
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
}

