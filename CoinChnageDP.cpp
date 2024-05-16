#include <vector>
#include <iostream>
#include <climits>

int coin_change(const std::vector<int>& denominations, int amount) {
    // Allocate a 2D array
    int** dp = new int* [denominations.size() + 1];
    for (int i = 0; i <= denominations.size(); i++) { // include the last index
        dp[i] = new int[amount + 1];
        // Initialize all to INT_MAX for minimum coin count
        for (int j = 0; j <= amount; j++) { // also include the last index
            dp[i][j] = INT_MAX;
        }
    }

    // Set base case for amount 0, requiring 0 coins
    for (int i = 0; i <= denominations.size(); i++) {
        dp[i][0] = 0; // No coins needed for zero amount
    }

    // Fill the dp table
    for (int i = 1; i <= denominations.size(); i++) { // Include the last denomination
        int coin = denominations[i - 1]; // The current denomination
        for (int j = 1; j <= amount; j++) {
            if (coin > j) {
                // If the coin denomination is greater than the current amount
                dp[i][j] = dp[i - 1][j]; // Use the previous row's solution
            }
            else {
                // Otherwise, choose the minimum between excluding or including the coin
                dp[i][j] = std::min(dp[i - 1][j], dp[i][j - coin] + 1); // Including the coin
            }
        }
    }

    int result = dp[denominations.size()][amount];

    // Clean up memory to prevent leaks
    for (int i = 0; i <= denominations.size(); i++) {
        delete[] dp[i];
    }
    delete[] dp;

    return result; // Return the minimum coin count for the given amount
}

void run_coin_change() {
    std::vector<int> denominations = { 1, 5, 7, 10 };
    int amount = 12;

    int result = coin_change(denominations, amount);
    std::cout << "Result: " << result << std::endl;
}

//int main() {
//    run_coin_change();
//    return 0;
//}
