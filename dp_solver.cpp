#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long ll;

// DP Gimkit Solver
// Developed by Ta180m

// Initial conditions
ll start = 0, goal = 1e10;
int max_it = 150; // Number of iterations to solve
// int MPQ = 0, SB = 0, M = 0; // Initial upgrade status
// int D, R, B1, B2; // Initial power-up status

// State: Iteration, Upgrade status, Power-up status
ll DP[7200000], pre[7200000];

// Return DP array element from state
ll& get_DP(int it, int MPQ, int SB, int M, int D, int R, int B1, int B2) {
    return DP[36000 * it + 3600 * MPQ + 360 * SB + 36 *M + 18 * D + 9 * R + 3 * B1 + B2];
}

// Return pre array element from state
ll& get_pre(int it, int MPQ, int SB, int M, int D, int R, int B1, int B2) {
    return pre[36000 * it + 3600 * MPQ + 360 * SB + 36 *M + 18 * D + 9 * R + 3 * B1 + B2];
}

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


int main() {
    memset(DP, -1, sizeof(DP));
    
    get_DP(0, 0, 0, 0, 0, 0, 0, 0) = start;
    for (int i = 0; i < 36000 * max_it; i++) {
        if (DP[i] != -1) {
            int it = i / 36000;
            int MPQ = (i / 3600) % 10, SB = (i / 360) % 10, M = (i / 36) % 10;
            int D = (i / 18) % 2, R = (i / 9) % 2, B1 = (i / 3) % 3, B2 = i % 3;
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
    
    for (int i = 0; i < 36000 * max_it; i++) {
        if (DP[i] >= goal) {
            for (int j = i; j != 0; j = pre[j]) {
                int it = j / 36000;
                int MPQ = (j / 3600) % 10, SB = (j / 360) % 10, M = (j / 36) % 10;
                int D = (j / 18) % 2, R = (j / 9) % 2, B1 = (j / 3) % 3, B2 = j % 3;
                cout << DP[j] << " " << it << " " << MPQ << " " << SB << " " << M << " " << D << " " << R << " " << B1 << " " << B2 << endl;
            }
            return 0;
        }
    }
}
