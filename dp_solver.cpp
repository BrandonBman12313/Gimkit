#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long ll;

// DP Gimkit Solver
// Developed by SAMCHOOO

// Initial conditions
ll start = 0, goal = 1e10;
int it = 150;

// State: Iteration, Upgrade status, Power-up status
ll DP[200][1000][36];

// Upgrade values and costs
double val[3][10] = {
    { 1, 5, 50, 100, 500, 2000, 5000, 10000, 250000, 1000000 },
    { 2, 20, 100, 200, 1000, 4000, 10000, 50000, 1000000, 5000000 },
    { 1, 1.5, 2, 3, 5, 8, 12, 18, 30, 100 }
};
ll cost[2][3][10] = {
    { { 0, 10, 100, 1000, 10000, 75000, 300000, 1000000, 10000000, 100000000},
    { 0, 15, 150, 1500, 15000, 115000, 450000, 1500000, 15000000, 200000000 },
    { 0, 50, 300, 2000, 12000, 85000, 700000, 6500000, 65000000, 1000000000 } },
    { { 0, 8, 75, 750, 7500, 56250, 225000, 750000, 7500000, 75000000 },
    { 0, 12, 113, 1125, 11250, 86250, 337500, 1125000, 11250000, 150000000 },
    { 0, 38, 225, 1500, 9000, 63750, 525000, 4875000, 48750000, 750000000 } }
};

// Power-up costs
int pcost[4] = { 250, 1000, 20, 50 };
double pcentcost[4] = { 0.16, 0.30, 0.03, 0.06 };
ll calc_pcost(int i, ll money) { return 5 * ceil((double)(pcentcost[i] * money + pcost[i]) / 5); }

int main() {
    memset(DP, -1, sizeof(DP));
    DP[0][0][0] = 0;
    for (int i = 0; i < it; i++) {
        for (int j = 0; j < 1000; j++) {
            int MPQ = j / 100, SB = (j / 10) % 10, M = j % 10;
            for (int k = 0; k < 36; k++) {
                if (DP[i][j][k] != -1) {
                    int D = (k / 18) % 2, R = (k / 9) % 2, B1 = (k / 3) % 3, B2 = k % 3;
                    ll money = DP[i][j][k], inc = round((val[0][MPQ] + (i != 0 ? val[1][SB] : 0)) * val[2][M]);
                    
                    // Answer a question
                    if (money + inc > DP[i + 1][j][k]) {
                        DP[i + 1][j][k] = money + inc;
                        // pre[v] = u;
                    }
                    
                    // Answer a question using the mini bonus
                    if (B1 == 1 && 2 * money + inc > DP[i + 1][j][k + 3]) {
                        DP[i + 1][j][k + 3] = 2 * money + inc;
                        // pre[v] = u;
                    }
                    
                    // Answer a question using the mega bonus
                    if (B2 == 1 && 5 * money + inc > DP[i + 1][j][k + 1]) {
                        DP[i + 1][j][k + 1] = 5 * money + inc;
                        // pre[v] = u;
                    }
                    
                    // Answer a question using both the mini bonus and the mega bonus
                    if (B1 == 1 && B2 == 1 && 10 * money + inc > DP[i + 1][j][k + 4]) {
                        DP[i + 1][j][k + 4] = 10 * money + inc;
                        // pre[v] = u;
                    }
                    
                    // Upgrade money per question
                    if (MPQ < 9 && money >= cost[D][0][MPQ + 1] && money - cost[D][0][MPQ + 1] > DP[i][j + 100][k]) {
                        DP[i][j + 100][k] = money - cost[D][0][MPQ + 1];
                        // pre[v] = u;
                    }
                    
                    // Upgrade streak bonus
                    if (SB < 9 && money >= cost[D][1][SB + 1] && money - cost[D][1][SB + 1] > DP[i][j + 10][k]) {
                        DP[i][j + 10][k] = money - cost[D][1][SB + 1];
                        // pre[v] = u;
                    }
                    
                    // Upgrade multiplier
                    if (M < 9 && money >= cost[D][2][M + 1] && money - cost[D][2][M + 1] > DP[i][j + 1][k]) {
                        DP[i][j + 1][k] = money - cost[D][2][M + 1];
                        // pre[v] = u;
                    }
                    
                    // Buy the discounter
                    if (D == 0 && money >= calc_pcost(0, money) && money - calc_pcost(0, money) > DP[i][j][k + 18]) {
                        DP[i][j][k + 18] = money - calc_pcost(0, money);
                        // pre[v] = u;
                    }
                    
                    // Buy the rebooter
                    if (R == 0 && money >= calc_pcost(1, money) && money - calc_pcost(1, money) > DP[i][j][9]) {
                        DP[i][j][9] = money - calc_pcost(1, money);
                        // pre[v] = u;
                    }
                    
                    // Buy the mini bonus
                    if (B1 == 0 && money >= calc_pcost(2, money) && money - calc_pcost(2, money) > DP[i][j][k + 2]) {
                        DP[i][j][k + 2] = money - calc_pcost(2, money);
                        // pre[v] = u;
                    }
                    
                    // Buy the mega bonus
                    if (B2 == 0 && money >= calc_pcost(3, money) && money - calc_pcost(3, money) > DP[i][j][k + 1]) {
                        DP[i][j][k + 1] = money - calc_pcost(3, money);
                        // pre[v] = u;
                    }
                }
            }
        }
    }
    
    // Find and print solution
    for (int i = 0; i < it; i++) {
        for (int j = 0; j < 1000; j++) {
            // int MPQ = j / 100, SB = (j / 10) % 10, M = j % 10;
            for (int k = 0; k < 36; k++) {
                // int D = (k / 18) % 2, R = (k / 9) % 2, B1 = (k / 3) % 3, B2 = k % 3;
                if (DP[i][j][k] > goal) {
                    cout << i << " " << j << " " << k << endl;
                    
                    /*for (state p = u; !(p == s); p = pre[p]) {
                        cout << p.MPQ << " " << p.SB << " " << p.M << " " << p.D << " " << p.R << " " << p.B1 << " " << p.B2 << endl;
                    }*/
                    return 0;
                }
            }
        }
    }
    
    /*vector<int> output;
    for (int i = 999; i != 0; i = pre[i]) output.push_back(i);
    output.push_back(0);
    reverse(output.begin(), output.end());
    
    for (int i = 1; i < output.size(); i++) {
        if (output[i] / 100 != output[i - 1] / 100) {
            cout << left << setw(25) << ("Upgrade MPQ to L" + format_int(output[i] / 100 + 1));
            cout << left << setw(25) << (" Cost: " + format_int(cost[output[i] / 100][0]));
            // cout << left << setw(25) << (" Remainder: " + format_int(rem[output[i]]));
        }
        else if ((output[i] / 10) % 10 != (output[i - 1] / 10) % 10) {
            cout << left << setw(25) << ("Upgrade SB to L" + format_int((output[i] / 10) % 10 + 1));
            cout << left << setw(25) << (" Cost: " + format_int(cost[(output[i] / 10) % 10][1]));
            // cout << left << setw(25) << (" Remainder: " + format_int(rem[output[i]]));
        }
        else {
            cout << left << setw(25) << ("Upgrade M to L" + format_int(output[i] % 10 + 1));
            cout << left << setw(25) << (" Cost: " + format_int(cost[output[i] % 10][2]));
            // cout << left << setw(25) << (" Remainder: " + format_int(rem[output[i]]));
        }
        cout << " Number of questions: " << DP[output[i]] - DP[output[i - 1]] << endl;    
    }
    cout << "Total questions: " << DP[999] + 2 << endl;*/
}
