#include <iostream>
#include <vector>
#include <climits>

int main()
{
    std::vector<int> denominations = {1, 2, 5, 10, 20, 50, 100, 500};
    int bill, amount;
    std::cout << "Enter bill amount: " << std::endl;
    std::cin >> bill;
    std::cout << "Enter amount given: " << std::endl;
    std::cin >> amount;

    int change = amount - bill;

    // Initialize the dp table
    std::vector<int> dp(change + 1, INT_MAX);
    std::vector<int> coins(change + 1, -1);
    dp[0] = 0;

    // Compute the minimum coins for all amounts up to the target amount
    for (int i = 1; i <= change; i++)
    {
        for (int j = 0; j < denominations.size(); j++)
        {
            if (denominations[j] <= i)
            {
                if (dp[i - denominations[j]] + 1 < dp[i])
                {
                    dp[i] = dp[i - denominations[j]] + 1;
                    coins[i] = denominations[j];
                }
            }
        }
    }

    // Check if solution exi.0ts
    if (dp[change] != INT_MAX)
    {
        std::cout << "Minimum coins required: " << dp[change] << std::endl;
        std::cout << "Coins used: ";
        int remaining_change = change;
        while (remaining_change > 0)
        {
            std::cout << coins[remaining_change] << " ";
            remaining_change -= coins[remaining_change];
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "No solution possible" << std::endl;
    }

    return 0;
}
