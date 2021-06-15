#include "vector.h"

FILE *file;
int restart = -1;
int arr[length];
short last = 0;

short is_full()
{
    if (last == length)
    {
        restart++;
        return 1;
    }
    return 0;
}

short is_empty()
{
    if (last == 0)
    {
        restart++;
        return 1;
    }
    return 0;
}

void push_back()
{
    arr[last] = ++last;
    printf("push %d\n", arr[last - 1]);
}

void pop_back()
{
    last--;
    printf("pop %d\n", arr[last]);
}

int getelem(short p) { return (p) ? arr[last - p] : arr[last]; }
