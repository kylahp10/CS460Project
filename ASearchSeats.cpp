#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

// Structure to represent a seat
struct Seat {
    int row, col;   // Position of the seat in the grid
    int cost;       // Cost of the seat

    // Comparison operator for priority queue (min-heap)
    bool operator<(const Seat& other) const {
        return cost > other.cost;
    }
};

// heuristic function to estimate the cost from current seat to goal seat considering price and distance
double heuristic(const Seat& currentSeat, const Seat& goalSeat, const vector<vector<int>>& priceGrid) {
    // Manhattan distance between current seat and goal seat
    double manhattan = abs(currentSeat.row - goalSeat.row) + abs(currentSeat.col - goalSeat.col);

    // Price of the current seat
    int currentPrice = priceGrid[currentSeat.row][currentSeat.col];

    // Price of the goal seat
    int goalPrice = priceGrid[goalSeat.row][goalSeat.col];

    // Combining distance and price
    double priceDifference = goalPrice - currentPrice;
    double heuristicValue = manhattan + priceDifference;    // Adjust the heuristic to prefer seats with lower prices relative to the goal

    return heuristicValue;
}


// Function to find the optimal path of seats using A* algorithm with custom heuristic
vector<Seat> findOptimalSeats(const vector<vector<int>>& availabilityGrid, const vector<vector<int>>& priceGrid, const Seat& startSeat, const Seat& goalSeat) {
    priority_queue<Seat> openSet; // Priority queue for open set
    openSet.push(startSeat); // Add the starting seat to the open set

    // Initialize costFromStart with infinity
    vector<vector<int>> costFromStart(availabilityGrid.size(), vector<int>(availabilityGrid[0].size(), numeric_limits<int>::max()));
    costFromStart[startSeat.row][startSeat.col] = startSeat.cost;

    // To keep track of the path
    vector<vector<Seat>> cameFrom(availabilityGrid.size(), vector<Seat>(availabilityGrid[0].size(), {-1, -1}));

    while (!openSet.empty()) {
        Seat currentSeat = openSet.top(); // Get the seat with the lowest cost
        openSet.pop();

        // If the goal is reached, reconstruct the path
        if (currentSeat.row == goalSeat.row && currentSeat.col == goalSeat.col) {
            vector<Seat> path;
            while (currentSeat.row != -1) {
                path.push_back(currentSeat);
                currentSeat = cameFrom[currentSeat.row][currentSeat.col];
            }
            reverse(path.begin(), path.end());
            return path;
        }

        // Directions for adjacent seats
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (const auto& direction : directions) {
            int newRow = currentSeat.row + direction.first;
            int newCol = currentSeat.col + direction.second;

            // Check if the new seat is within the grid and available
            if (newRow >= 0 && newRow < availabilityGrid.size() && newCol >= 0 && newCol < availabilityGrid[0].size() && availabilityGrid[newRow][newCol] == 1) {
                int tentativeCostFromStart = costFromStart[currentSeat.row][currentSeat.col] + priceGrid[newRow][newCol];

                // If the new path is better, update the path and costs
                if (tentativeCostFromStart < costFromStart[newRow][newCol]) {
                    cameFrom[newRow][newCol] = currentSeat;
                    costFromStart[newRow][newCol] = tentativeCostFromStart;
                    double estimatedTotalCost = tentativeCostFromStart + heuristic({newRow, newCol, priceGrid[newRow][newCol]}, goalSeat, priceGrid);
                    openSet.push({newRow, newCol, priceGrid[newRow][newCol]});
                }
            }
        }
    }
    return {}; // No path found
}

int main() {
    // Grid representing seat availability (1 for available, 0 for unavailable)
    vector<vector<int>> availabilityGrid = {
            {1, 1, 1, 1},
            {1, 0, 1, 1},
            {1, 1, 1, 1},
            {1, 1, 1, 1},
    };

    // Grid representing seat prices
    vector<vector<int>> priceGrid = {
            {50, 20, 40, 50},
            {20, 30, 30, 40},
            {10, 20, 30, 40},
            {10, 20, 30, 40},
    };

    Seat startSeat = {3, 0, 10};  // Starting seat at (3, 0) with price 10 (bottom-left corner)
    Seat goalSeat = {0, 2, 40};   // Goal seat at (0, 2) with price 40

    // Find the optimal path of seats
    vector<Seat> optimalPath = findOptimalSeats(availabilityGrid, priceGrid, startSeat, goalSeat);

    // Display the optimal path
    if (!optimalPath.empty()) {
        cout << "Optimal seats found:" << endl;
        for (const auto& seat : optimalPath) {
            cout << "(" << seat.row << ", " << seat.col << ") with price " << seat.cost << endl;
        }
    } else {
        cout << "No optimal seats found." << endl;
    }

    return 0;
}