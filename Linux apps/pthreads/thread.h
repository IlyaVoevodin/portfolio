#include "vector.h"
#define repeat 3

extern pthread_t p1, p2, p3, p4, p5, p6;

extern pthread_cond_t not_empty, not_full, Sig21, Sig22;
extern pthread_mutex_t MCR1, M_Sig21, M_Sig22;
extern sem_t SCR21;

extern int int_1, int_2;
extern unsigned unsigned_1, unsigned_2;
extern long long_1, long_2;
extern unsigned long unsigned_long_1, unsigned_long_2;

void *p1_func(void *th);
void *p2_func(void *th);
void *p3_func(void *th);
void *p4_func(void *th);
void *p5_func(void *th);
void *p6_func(void *th);