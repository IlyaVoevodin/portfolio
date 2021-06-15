#include "Print.h"

void pretty_print(const int n, int* A)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d\t", *(A + i*n + j));
        }
        printf("\n\n");
    }
}

void menu(const int n, int** A)
{
    int var;
    printf("Choose type of matrix filler:\n 1)Keyboard\n 2)Rand\n 3)Sorted\n Print number to choose:");
    scanf("%d", &var);
    switch (var)
    {
    case 1: {HandInput(n,A); pretty_print(n, *A); break; }
    case 2: {RandInput(n, A); pretty_print(n, *A); break; }
    case 3: {SortedInput(n, A); pretty_print(n, *A); break; }
        default: 
        { printf("Wrong input");
        break; }
    }

}