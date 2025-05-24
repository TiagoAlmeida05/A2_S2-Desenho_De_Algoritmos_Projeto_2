#!/bin/bash

# Compile first
echo "Compiling..."
g++ -std=c++17 Main.cpp functions.cpp -o knapsack -O3
if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

# Get the directory where this script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# Define datasets to test
datasets=("01" "02" "03" "04")  # Add your dataset suffixes

for ds in "${datasets[@]}"; do
    echo -e "\n=== Testing dataset $ds ==="
    
    # Define full file paths
    TRUCK_FILE="${SCRIPT_DIR}/TruckAndPallets_${ds}.csv"
    PALLETS_FILE="${SCRIPT_DIR}/Pallets_${ds}.csv"
    
    # Verify files exist
    if [ ! -f "$TRUCK_FILE" ]; then
        echo "Error: Truck file not found: $TRUCK_FILE"
        continue
    fi
    if [ ! -f "$PALLETS_FILE" ]; then
        echo "Error: Pallets file not found: $PALLETS_FILE"
        continue
    fi
    
    # Run the program with the files
    echo -e "1\n${TRUCK_FILE}\n${PALLETS_FILE}\n2\n3\n4\n5\n6\n7" | ./knapsack
    
    echo "----------------------------------"
done