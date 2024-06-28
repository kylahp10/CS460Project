# CS460 Project - Improve Ticket Purchasing System using A* Search Algorithm

*STARTER*
*STILL NEEDS A LOT OF WORK AND TESTING*

How this algorithm would benefit these ticket systems:
- Improve user experience
- Optimize seat allocation
- Enhance ticket purchasing system 
- Can handle complex and large grids -> big concert venues

Heuristic function:

- Combines Manhattan distance and price differences between seats.
- Estimates the total cost from the current seat to the goal seat.

A* search implementation:

- Uses priority queue to manage seats being explored, prioritized by estimated total cost 
- Cost and path tracking using matrices to track minimum costs and optimal paths


For test simplicity:

- Start node: farthest row, cheapest seat
- Goal node: first row, price of 40

Output:
- Prints optimal path found 
- Seat coordinates + price of seat

Considerations for improving/expanding on my implementation:

- Additional constraints
- Real time updates
- Multiple goal seats 
- Testing different grids
- Finding the best heuristic function 
