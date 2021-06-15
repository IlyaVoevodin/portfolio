#include "Input.h"

void HandInput(const int n, int** A)
{
    int val;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n ; j++)
        {
            printf("Input value for [%d][%d]:", i, j);
            scanf("%d", &val);
            (*(*A + i * n + j)) = val;
        }
    }
}

void SortedInput(const int n, int** A)
{
    int matrix[N][N] = {
        { 21, 34, 56, 22, 76, 90, 36, 47, 83, 14},
        { 45, 10, 17, 84, 62, 49, 58, 55, 13, 98},
        { 16, 26, 82, 67, 15, 65, 12, 24 , 15, 33},
        { 79, 13, 57, 44, 38, 94, 11, 47, 49, 86},
        { 46, 12, 64, 83, 47, 23, 10, 21, 30 ,66},
        { 34, 75, 14, 73, 52, 39, 27, 32, 11, 78},
        { 45, 27, 48, 18, 95, 60, 71, 76, 88 ,37},
	{ 76, 10, 46, 83, 27, 18, 72, 92, 37, 58},
	{ 14, 41, 62, 72, 17, 48, 39, 94, 93, 77},
	{ 15, 67, 73, 45, 47, 37, 74, 59, 37, 28}
    };
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            (*(*A + i * n + j)) = matrix[i][j];
        }
    }
}

void RandInput(const int n, int** A)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            (*(*A + i*n + j)) = rand() % 100;
        }
    }
}