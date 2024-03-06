#include <iostream>

int *weight;
int *profit;
int size;
int knapsack_size;
float *profit_by_weight;

void get_input()
{
    std::cout << "Enter a Size: ";
    std::cin >> size;
    weight = (int *)calloc(size, sizeof(0));
    profit = (int *)calloc(size, sizeof(0));
    profit_by_weight = (float *)calloc(size, sizeof(float));

    for (int i = 0; i < size; i++)
    {
        std::cout << "Enter Weight_" << i << ":";
        std::cin >> weight[i];
        std::cout << "Enter Profit_" << i << ":";
        std::cin >> profit[i];
    }

    std::cout << "Enter KnapSack Size: ";
    std::cin >> knapsack_size;
}

void calc_profit_by_wt()
{
    for (int i = 0; i < size; i++)
    {
        if (weight[i] == 0)
        {
            std::cout << "Weight cannot be negetive" << std::endl;
            return;
        }

        profit_by_weight[i] = profit[i] / weight[i];
    }
}

void sort_by_pw()
{
    for (int i = 0; i < size - 1; i++) // Change the condition to size - 1
    {
        bool swapped = false;
        for (int j = 0; j < size - i - 1; j++) // Adjust the loop to bubble sort
        {
            if (profit_by_weight[j] < profit_by_weight[j + 1])
            {
                float temp_profit = profit_by_weight[j];
                profit_by_weight[j] = profit_by_weight[j + 1];
                profit_by_weight[j + 1] = temp_profit;

                int temp_profit_index = j;
                int temp_profit_ = profit[j];
                profit[j] = profit[j + 1];
                profit[j + 1] = temp_profit_;

                int temp_weight = weight[j];
                weight[j] = weight[j + 1];
                weight[j + 1] = temp_weight;

                swapped = true;
            }
        }
        if (!swapped)
            break; // No swaps in this pass, so we're done
    }

    for (int i = 0; i < size; i++)
    {
        std::cout << " P/w " << profit_by_weight[i] << " p " << profit[i] << " w " << weight[i] << "\n";
    }
}

void knapsack()
{
    int cp = 0; // Initialize cp to 0
    int cw = 0; // Initialize cw to 0
    for (int i = 0; i < size; i++)
    {
        if (cw + weight[i] <= knapsack_size)
        {
            cw += weight[i];
            cp += profit[i];

            std::cout << "We use " << weight[i] << " object completely (1): Cummulative Profit: " << cp << std::endl;
        }
        else
        {
            std::cout << "We use " << weight[i] << " object partially (" << (float)(1.0f * (knapsack_size - cw) / weight[i]) << "): Cummulative Profit: " << cp << std::endl;
            cp += profit[i] * (1.0f * (knapsack_size - cw) / weight[i]);
            cw = knapsack_size;
        }
    }

    std::cout << "Total Profit: " << cp << std::endl;
}

int main()
{
    get_input();
    calc_profit_by_wt();
    sort_by_pw();
    knapsack();
    return 0;
}