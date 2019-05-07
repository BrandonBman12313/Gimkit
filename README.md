# Gimkit
Using a Dynamic Programming algorithm to search for the optimal Gimkit strategy.

## How to use
```
// Initial conditions
// Change these values to alter the initial state
ll start = 0, goal = 1e10;
int max_it = 150; // Number of iterations to solve
int MPQ = 0, SB = 0, M = 0; // Initial upgrade status
int D = 0, R = 0, B1 = 0, B2 = 0; // Initial power-up status
```

Change these values to alter the initial state:
* **start** - Starting amount of money
* **goal** - Ending amount of money
* **max_it** - The maximum number of iterations to solve
* **MPQ** - The initial level of the money per question upgrade (Starts from 0)
* **SB** - The initial level of the streak bonus upgrade (Starts from 0)
* **M** - The initial level of the multiplier upgrade (Starts from 0)
* **D** - The status of the discounter power-up (0 is unpurchased, 1 is purchased and used)
* **R** - The status of the rebooter power-up (0 is unpurchased, 1 is purchased and used)
* **B1** - The status of the mini bonus power-up (0 is unpurchased, 1 is purchased and unused, 2 is used)
* **B2** - The status of the mega bonus power-up (0 is unpurchased, 1 is purchased and unused, 2 is used)
