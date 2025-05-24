#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include "functions.h"

using namespace std;

void displayMenu();
void loadTruck(int& capacity, int& pallets);
vector<item> loadPallets();

int main() {        
    int capacity = 0, pallets = 0; 
    vector<item> values;
    system("cls || clear");  // Works for both Windows and Unix
    
    char choice;
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        // Variables declared outside switch to avoid scope issues
        chrono::time_point<chrono::high_resolution_clock> start, end;
        double duration;

        switch (choice) {
            case '1': {
                loadTruck(capacity, pallets);
                values = loadPallets();
                break;
            }
            case '2': {
                if (values.empty()) {
                    cout << "Error: Load truck and pallets first!\n";
                    break;
                }
                start = chrono::high_resolution_clock::now();
                int profit=bruteForce(values, capacity);
                end = chrono::high_resolution_clock::now();
                duration = chrono::duration<double, milli>(end-start).count();
                logResult("Brute Force", values.size(), capacity, duration, profit);
                break;
            }
            case '3': {
                if (values.empty()) {
                    cout << "Error: Load truck and pallets first!\n";
                    break;
                }
                start = chrono::high_resolution_clock::now();
                int profit=backtracking(values, capacity);
                end = chrono::high_resolution_clock::now();
                duration = chrono::duration<double, milli>(end-start).count();
                logResult("Backtracking", values.size(), capacity, duration,profit);
                break;
            }
            case '4': {
                if (values.empty()) {
                    cout << "Error: Load truck and pallets first!\n";
                    break;
                }
                start = chrono::high_resolution_clock::now();
                int profit =dynamicProgramming(values, capacity);
                end = chrono::high_resolution_clock::now();
                duration = chrono::duration<double, milli>(end-start).count();
                logResult("Dynamic Programming", values.size(), capacity, duration,profit);
                break;
            }
            case '5': {
                if (values.empty()) {
                    cout << "Error: Load truck and pallets first!\n";
                    break;
                }
                start = chrono::high_resolution_clock::now();
                int profit=approximation(values, capacity);
                end = chrono::high_resolution_clock::now();
                duration = chrono::duration<double, milli>(end-start).count();
                logResult("Greedy", values.size(), capacity, duration,profit);
                break;
            }
            case '6': {
                if (values.empty()) {
                    cout << "Error: Load truck and pallets first!\n";
                    break;
                }
                start = chrono::high_resolution_clock::now();
                int profit =ilpAlgorithm(values, capacity);
                end = chrono::high_resolution_clock::now();
                duration = chrono::duration<double, milli>(end-start).count();
                logResult("ILP", values.size(), capacity, duration,profit);
                break;
            }
            case '7': {
                cout << "Exiting Program...\n";
                break;
            }
            default:
                cout << "Invalid choice\n";
        }
    } while (choice != '7');

    return 0;
}

void logResult(const string& algo, int pallets, int capacity, double time_ms,int profit) {
    ofstream out("results.csv", ios::app);
    out << algo << "," << pallets << "," << capacity << "," << time_ms << ","<< profit<<"\n";
    out.close();
}

void displayMenu() {
    cout << "\n===== Pallet Packing Optimization Tool =====\n";
    cout << "1. Select Truck and Pallets\n";
    cout << "2. Brute-Force Approach\n";
    cout << "3. Backtracking Approach\n";
    cout << "4. Dynamic Programming\n";
    cout << "5. Greedy Algorithm\n";
    cout << "6. ILP Algorithm\n";
    cout << "7. Exit\n";
}

void loadTruck(int& capacity, int& pallets) {
    string filename;
    cout << "Enter Truck File Name (e.g., TruckAndPallets_01.csv): ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open " << filename << "!\n";
        return;
    }

    string line;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string capa, pal;
        getline(ss, capa, ',');
        getline(ss, pal, ',');
        capacity = stoi(capa);
        pallets = stoi(pal);
    }
}

vector<item> loadPallets() {
    vector<item> values;
    string filename;
    cout << "Enter Pallets File Name (e.g., Pallets_01.csv): ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open " << filename << "!\n";
        return values;
    }

    string line;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string id, w, p;
        getline(ss, id, ',');
        getline(ss, w, ',');
        getline(ss, p, ',');
        values.push_back({stoi(w), stoi(p)});
    }

    return values;
}