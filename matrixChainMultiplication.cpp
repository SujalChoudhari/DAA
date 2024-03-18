#include <iostream>
#include <algorithm>

int main()
{
    int d[5] = {0}; // Initialize the array with zeros

    // Input for Matrix 1
    std::cout << "Enter the number of rows for Matrix 1: ";
    std::cin >> d[0];

    // Input for Matrix 1-2
    std::cout << "Enter the number of columns for Matrix 1 (and rows for Matrix 2): ";
    std::cin >> d[1];

    // Input for Matrix 2-3
    std::cout << "Enter the number of columns for Matrix 2 (and rows for Matrix 3): ";
    std::cin >> d[2];

    // Input for Matrix 3-4
    std::cout << "Enter the number of columns for Matrix 3 (and rows for Matrix 4): ";
    std::cin >> d[3];

    // Input for Matrix 4
    std::cout << "Enter the number of columns for Matrix 4: ";
    std::cin >> d[4];

    int COST[5][5] = {{0}};
    int K[5][5] = {{0}};

    // Initialize diagonal as 0 and null
    for (int i = 0; i < 4; i++)
    {
        COST[i][i] = 0;
        K[i][i] = -1;
    }

    for (int i = 0; i <= 4; i++)
    {
        for (int m = 1; m <= 3; m++)
        {
            int j = i + m;
            int curr_min = 99999;
            for (int k = i; k < j; k++)
            {
                curr_min = std::min(curr_min, COST[i][k] + COST[k + 1][j] + d[i - 1] * d[k] * d[j]);
            }
            COST[i][j] = curr_min;
        }
    }

    for (int i =0;i <= 4; i++){
        for(int j=0;j<=4;j++){
            std::cout << COST[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
