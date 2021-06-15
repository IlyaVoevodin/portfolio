#include "Search.h"

void ReleaseSearch(int x, int* row_x, int* clmn_x, const int n, int* A)
{
    for (int i = 0; i < n; i++)
    {
        int j = n - i - 1;

        if (*(A + i * n + j) == x)
        {
            *row_x = i + 1;
            *clmn_x = j + 1;
            return;
        }
        else
        {
            if ((i == n - 1) && (j == 0))
            {
                *row_x = 0;
                *clmn_x = 0;
            }
        }
    }
}

void DebugSearch(int x, int* row_x, int* clmn_x, const int n, int* A)
{
    for (int i = 0; i < n; i++)
    {   
        int j = n - i - 1;
               
        printf("Searching...\n Current value: %d\n", *(A + i * n + j));
        if (*(A + i * n + j) == x)
        {   
            *row_x = i + 1;
            *clmn_x = j + 1;
            printf("Value %d was found at [%d][%d]", x, *row_x, *clmn_x);
            return;
        }
        else
        {   
            if ((i == n - 1) && (j == 0))
            {   
                printf("Value %d was not found!", x);
                *row_x = 0;
                *clmn_x = 0;
            }
        }
    }
}