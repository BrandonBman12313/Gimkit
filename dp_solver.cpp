#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long ll;

// DP Gimkit Solver
// Developed by Ta180m

// Initial conditions
ll start = 0, goal = 1e10;
int max_it = 150; // Number of iterations to solve
int MPQ = 0, SB = 0, M = 0; // Initial upgrade status
int D, R, B1, B2; // Initial power-up status

// Initial state
int s = 3600 * MPQ + 360 * SB + 36 * M + 18 * D + 9 * R + 3 * B1 + B2;

// State: Iteration, Upgrade status, Power-up status
// DP stores maximum possible money for each state
// pre used to reconstruct optimal strategy
ll DP[7200000], pre[7200000];

// Upgrade values
double val[3][10] = {
    { 1, 5, 50, 100, 500, 2000, 5000, 10000, 250000, 1000000 },
    { 2, 20, 100, 200, 1000, 4000, 10000, 50000, 1000000, 5000000 },
    { 1, 1.5, 2, 3, 5, 8, 12, 18, 30, 100 }
};

// Upgrade costs
ll cost[2][3][10] = {
    { { 0, 10, 100, 1000, 10000, 75000, 300000, 1000000, 10000000, 100000000},
    { 0, 15, 150, 1500, 15000, 115000, 450000, 1500000, 15000000, 200000000 },
    { 0, 50, 300, 2000, 12000, 85000, 700000, 6500000, 65000000, 1000000000 } },
    { { 0, 8, 75, 750, 7500, 56250, 225000, 750000, 7500000, 75000000 },
    { 0, 12, 113, 1125, 11250, 86250, 337500, 1125000, 11250000, 150000000 },
    { 0, 38, 225, 1500, 9000, 63750, 525000, 4875000, 48750000, 750000000 } }
};

// Power-up costs
int base[4] = { 250, 1000, 20, 50 };
double pcent[4] = { 0.16, 0.30, 0.03, 0.06 };
ll pcost(int i, ll x) { return 5 * ceil((double)(pcent[i] * x + base[i]) / 5); }

// Utility function to format output
string format(ll x) {
    string ret = to_string(x);
    int pos = ret.length() - 3;
    while (pos > 0) {
        ret.insert(pos, ",");
        pos -= 3;
    }
    return ret;
}

// Bottom-up DP algorithm
int main() {
    // Initialize DP array
    memset(DP, -1, sizeof(DP));
    
    // Set initial value
    DP[s] = start;
    for (int i = 0; i < 36000 * max_it; i++) {
        if (DP[i] != -1) {
            // Calculate parameters
            int it = i / 36000;
            int MPQ = (i / 3600) % 10, SB = (i / 360) % 10, M = (i / 36) % 10;
            int D = (i / 18) % 2, R = (i / 9) % 2, B1 = (i / 3) % 3, B2 = i % 3;
            
            // Income per question
            ll inc = round((val[0][MPQ] + (i != 0 ? val[1][SB] : 0)) * val[2][M]);
            
            // Answer a question
            if (DP[i] + inc > DP[i + 36000]) {
                DP[i + 36000] = DP[i] + inc;
                pre[i + 36000] = i;
            }
            
            // Answer a question using the mini bonus
            if (B1 == 1 && DP[i] + 2 * inc > DP[i + 36003]) {
                DP[i + 36003] = DP[i] + 2 * inc;
                pre[i + 36003] = i;
            }
            
            // Answer a question using the mega bonus
            if (B2 == 1 && DP[i] + 5 * inc > DP[i + 36001]) {
                DP[i + 36001] = DP[i] + 5 * inc;
                pre[i + 36001] = i;
            }
            
            // Answer a question using both the mini bonus and the mega bonus
            if (B1 == 1 && B2 == 1 && DP[i] + 10 * inc > DP[i + 36004]) {
                DP[i + 36004] = DP[i] + 10 * inc;
                pre[i + 36004] = i;
            }
            
            // Upgrade money per question
            for (int j = MPQ + 1; j < 10 && DP[i] >= cost[D][0][j]; j++) {
                if (DP[i] - cost[D][0][j] > DP[i + 3600 * (j - MPQ)]) {
                    DP[i + 3600 * (j - MPQ)] = DP[i] - cost[D][0][j];
                    pre[i + 3600 * (j - MPQ)] = i;
                }
            }
            
            // Upgrade streak bonus
            for (int j = SB + 1; j < 10 && DP[i] >= cost[D][1][j]; j++) {
                if (DP[i] - cost[D][1][j] > DP[i + 360 * (j - SB)]) {
                    DP[i + 360 * (j - SB)] = DP[i] - cost[D][1][j];
                    pre[i + 360 * (j - SB)] = i;
                }
            }
            
            // Upgrade streak bonus
            for (int j = M + 1; j < 10 && DP[i] >= cost[D][2][j]; j++) {
                if (DP[i] - cost[D][2][j] > DP[i + 36 * (j - M)]) {
                    DP[i + 36 * (j - M)] = DP[i] - cost[D][2][j];
                    pre[i + 36 * (j - M)] = i;
                }
            }
            
            // Buy the discounter
            if (D == 0 && DP[i] - pcost(0, DP[i]) > DP[i + 18]) {
                DP[i + 18] = DP[i] - pcost(0, DP[i]);
                pre[i + 18] = i;
            }
            
            // Buy the rebooter
            if (R == 0 && DP[i] - pcost(1, DP[i]) > DP[i - i % 36 + 9]) {
                DP[i - i % 36 + 9] = DP[i] - pcost(1, DP[i]);
                pre[i - i % 36 + 9] = i;
            }
            
            // Buy the mini bonus
            if (B1 == 0 && DP[i] - pcost(2, DP[i]) > DP[i + 2]) {
                DP[i + 2] = DP[i] - pcost(2, DP[i]);
                pre[i + 2] = i;
            }
            
            // Buy the mega bonus
            if (B2 == 0 && DP[i] - pcost(3, DP[i]) > DP[i + 1]) {
                DP[i + 1] = DP[i] - pcost(3, DP[i]);
                pre[i + 1] = i;
            }
        }
    }
    
    // Find the optimal solution
    int sol = 7200000;
    for (int i = 0; i < 36000 * max_it; i++) {
        if (i / 36000 > sol / 36000) break;
        if (DP[i] >= goal && (sol == 7200000 || DP[i] > DP[sol])) sol = i;
    }
    
    // Print output
    if (sol != 7200000) {
        vector<int> output;
        for (int i = sol; i != s; i = pre[i]) output.push_back(i);
        reverse(output.begin(), output.end());
        cout << "Iterations: " << sol / 36000 << endl;
        for (int i = 0; i < output.size(); i++) {
            int it = output[i] / 36000;
            int MPQ = (output[i] / 3600) % 10, SB = (output[i] / 360) % 10, M = (output[i] / 36) % 10;
            int D = (output[i] / 18) % 2, R = (output[i] / 9) % 2, B1 = (output[i] / 3) % 3, B2 = output[i] % 3;
            if (it != output[i - 1] / 36000) cout << right << setw(3) << it << ". ";
            else cout << "     ";
            if (it != output[i - 1] / 36000 && B1 == (output[i - 1] / 3) % 3 && B2 == output[i - 1] % 3) cout << "Answer 1 question, bringing your total up to $" << format(DP[output[i]]) << endl;
            else if (it != output[i - 1] / 36000 && B1 != (output[i - 1] / 3) % 3 && B2 == output[i - 1] % 3) cout << "Answer 1 question using the mini bonus, bringing your total up to $" << format(DP[output[i]]) << endl;
            else if (it != output[i - 1] / 36000 && B1 == (output[i - 1] / 3) % 3 && B2 != output[i - 1] % 3) cout << "Answer 1 question using the mega bonus, bringing your total up to $" << format(DP[output[i]]) << endl;
            else if (it != output[i - 1] / 36000 && B1 != (output[i - 1] / 3) % 3 && B2 != output[i - 1] % 3) cout << "Answer 1 question using both the mini and mega bonuses, bringing your total up to $" << format(DP[output[i]]) << endl;
            else if (MPQ != (output[i - 1] / 3600) % 10) cout << "Buy the Level " << MPQ << " ($" << format(val[0][MPQ]) << ") money per question upgrade for $" << format(cost[D][0][MPQ]) << ", making your total $" << format(DP[output[i]]) << endl;
            else if (SB != (output[i - 1] / 360) % 10) cout << "Buy the Level " << SB << " ($" << format(val[1][SB]) << ") streak bonus upgrade for $" << format(cost[D][1][SB]) << ", making your total $" << format(DP[output[i]]) << endl;
            else if (M != (output[i - 1] / 36) % 10) cout << "Buy the Level " << M << " (x" << format(val[2][M]) << ") multiplier for $" << format(cost[D][2][M]) << ", making your total $" << format(DP[output[i]]) << endl;
            else if (D != (output[i - 1] / 18) % 2) cout << "Buy and use the discounter for $" << format(pcost(0, DP[output[i - 1]])) << ", making your total $" << format(DP[output[i]]) << endl;
            else if (R != (output[i - 1] / 9) % 2) cout << "Buy and use the rebooter for $" << format(pcost(1, DP[output[i - 1]])) << ", making your total $" << format(DP[output[i]]) << endl;
            else if (B1 != (output[i - 1] / 3) % 3) cout << "Buy the mini bonus for $" << format(pcost(2, DP[output[i - 1]])) << ", making your total $" << format(DP[output[i]]) << endl;
            else if (B2 != output[i - 1] % 3) cout << "Buy the mega bonus for $" << format(pcost(3, DP[output[i - 1]])) << ", making your total $" << format(DP[output[i]]) << endl;
            else cout << "Error: Something went wrong" << endl;
        }
    }
    else cout << "No strategy to reach $" << goal << " from $" << start << " in " << max_it << " iterations could be found" << endl;
}
