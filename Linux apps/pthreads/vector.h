#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define length 3

extern FILE *file;
extern int restart;
extern int arr[length];
extern short last;

short is_full();
short is_empty();
void push_back();
void pop_back();
int getelem(short p);
