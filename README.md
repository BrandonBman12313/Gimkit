# Gimkit
Gimkit, an assessment tool with a monetary component, has been described as “Kahoot on steroids”, featuring upgrades and power-ups. These aspects make Gimkit a strategically intriguing and interesting game to analyze.

Ever wondered about what the optimal [Gimkit](https://gimkit.com) strategy is? Well, now you can get a definite answer with `dp_solver.cpp`, which uses a Dynamic Programming algorithm to search for the optimal Gimkit strategy. This algorithm can calculate the optimal strategy from any arbitary starting state.

See [this link](https://onlinegdb.com/rJNOKO324) to run `dp_solver.cpp`.

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
- **start** - Starting amount of money
- **goal** - Ending amount of money
- **max_it** - The maximum number of iterations to solve
- **MPQ** - The initial level of the money per question upgrade (Starts from 0)
- **SB** - The initial level of the streak bonus upgrade (Starts from 0)
- **M** - The initial level of the multiplier upgrade (Starts from 0)
- **D** - The status of the discounter power-up (0 is unpurchased, 1 is purchased and used)
- **R** - The status of the rebooter power-up (0 is unpurchased, 1 is purchased and used)
- **B1** - The status of the mini bonus power-up (0 is unpurchased, 1 is purchased and unused, 2 is used)
- **B2** - The status of the mega bonus power-up (0 is unpurchased, 1 is purchased and unused, 2 is used)

## How it works
Without considering player interactions, the *state* of a Gimkit game can actually be represented with only eight parameters: money, the levels of the money per question, streak bonus, and multiplier updates, and the status of four power-ups. For any such state, we want to minimize the number of questions ("iterations") needed to reach that state. However, money can range over a large range of values, so instead, we will swap money and the number of questions answered. Realistically, a player will only answer at most 200 questions, so this will reduce the total number of states. Note that a state only contains information about the current status in the game, not the particular path used to reach that state.

State parameters:
- **it** - The number of questions answered
- **MPQ** - The level of the money per question upgrade (Starts from 0)
- **SB** - The level of the streak bonus upgrade (Starts from 0)
- **M** - The level of the multiplier upgrade (Starts from 0)
- **D** - The status of the discounter power-up (0 is unpurchased, 1 is purchased and used)
- **R** - The status of the rebooter power-up (0 is unpurchased, 1 is purchased and used)
- **B1** - The status of the mini bonus power-up (0 is unpurchased, 1 is purchased and unused, 2 is used)
- **B2** - The status of the mega bonus power-up (0 is unpurchased, 1 is purchased and unused, 2 is used)

Now that we have our state, we must determine the state *transitions*. Some transitions include answering a question, using a power-up, or buying an upgrade. These transitions allow us to go from one state to another. For example, consider the transition of answering a question. The new state's iteration will be one larger, while everything else stays the same. Starting from the initial state, the algorithm traverses transitions in an attempt to reach a state with money greater than the goal.
