#include "thread.h"

pthread_t p1, p2, p3, p4, p5, p6;

int int_1, int_2;
unsigned unsigned_1, unsigned_2;
long long_1, long_2;
unsigned long unsigned_long_1, unsigned_long_2;

void *p1_func(void *th);
void *p2_func(void *th);
void *p3_func(void *th);
void *p4_func(void *th);
void *p5_func(void *th);
void *p6_func(void *th);

pthread_cond_t not_empty, not_full;
pthread_cond_t Sig21 = PTHREAD_COND_INITIALIZER;
pthread_cond_t Sig22 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t MCR1, M_Sig21, M_Sig22;
sem_t SCR21;

void *p1_func(void *th)
{
    fprintf(file, "Thread #1 START\n");
    while (1)
    {
        if (pthread_mutex_trylock(&MCR1))
        {
            fprintf(file, "Thread #1 WAITING FOR MCR1\n");
            while (pthread_mutex_trylock(&MCR1))
            {
            }
        }
        while (is_empty())                                      
        {
            pthread_cond_wait(&not_empty, &MCR1);               
        }
        pop_back();                                            
        fprintf(file, "Thread #1 POP ELEM %d\n", getelem(0));  
        pthread_mutex_unlock(&MCR1);
        pthread_cond_broadcast(&not_full);                      
        fprintf(file, "Thread #1 SCR21 POST\n");                
        sem_post(&SCR21);                                       
    }
    fprintf(file, "Thread #1 END\n");
}

void *p2_func(void *th)
{
    fprintf(file, "Thread #2 START\n");
    while (1)
    {
        pthread_mutex_lock(&M_Sig21);
        fprintf(file, "Thread #2 Sig21 WAIT\n");
        pthread_cond_wait(&Sig21, &M_Sig21);
        fprintf(file, "Thread #2 Sig21 GOTTEN\n");
        pthread_mutex_unlock(&M_Sig21);
        fprintf(file, "Thread #2 USED & MODIFIED\n");
        __sync_and_and_fetch(&unsigned_1, 10);
        __sync_fetch_and_and(&unsigned_2, 4);
        __sync_val_compare_and_swap(&int_2, 5, 10);

        if (pthread_mutex_trylock(&MCR1))
        {
            fprintf(file, "Thread #2 WAITING FOR MCR1\n");
            while (pthread_mutex_trylock(&MCR1))
            {
            }
        }
        while (is_full())                                       
        {
            pthread_cond_wait(&not_full, &MCR1);                
        }
        push_back();                                            
        fprintf(file, "Thread #2 PUSH ELEM %d\n", getelem(1));  
        pthread_mutex_unlock(&MCR1);
        pthread_cond_broadcast(&not_empty);                     
        fprintf(file, "Thread #2 Sig22 SIGNAL\n");
        pthread_cond_signal(&Sig22);
    }
    fprintf(file, "Thread #2 END\n");
}

void *p3_func(void *th)
{
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    fprintf(file, "Thread #3 START\n");
    fprintf(file, "Thread #3 MODIFIED\n");      
    __sync_bool_compare_and_swap(&int_1, 4, 2);
    while (1)
    {
        if (restart >= repeat)
        {
            break;
        }
        fprintf(file, "Thread #3 Sig21 BROADCAST\n");
        pthread_cond_broadcast(&Sig21);             
        fprintf(file, "Thread #3 MODIFIED\n");      
        __sync_val_compare_and_swap(&int_2, 2, 6);
    }
    fprintf(file, "Thread #3 END\n");
    pthread_cancel(p1);
    fprintf(file, "Thread #1 END\n");
    pthread_cancel(p2);
    fprintf(file, "Thread #2 END\n");
    pthread_cancel(p4);
    fprintf(file, "Thread #4 END\n");
    pthread_cancel(p5);
    fprintf(file, "Thread #5 END\n");
    pthread_cancel(p6);
    fprintf(file, "Thread #6 END\n");
}

void *p4_func(void *th)
{
    fprintf(file, "Thread #4 START\n");
    while (1)
    {
        if (pthread_mutex_trylock(&MCR1))
        {
            fprintf(file, "Thread #4 WAITING FOR MCR1\n");
            while (pthread_mutex_trylock(&MCR1))
            {
            }
        }
        while (is_full())                                       
        {
            pthread_cond_wait(&not_full, &MCR1);
        }
        push_back();                                            
        fprintf(file, "Thread #4 PUSH ELEM %d\n", getelem(1));  
        pthread_mutex_unlock(&MCR1);
        pthread_cond_broadcast(&not_empty);                     
        fprintf(file, "Thread #4 SCR21 WAIT\n");
        sem_trywait(&SCR21);                                       
        fprintf(file, "Thread #4 SCR21 GOTTEN\n");              
    }
    fprintf(file, "Thread #4 END\n");
   
}

void *p5_func(void *th)
{
    fprintf(file, "Thread #5 START\n");
    while (1)
    {
        pthread_mutex_lock(&M_Sig21);
        fprintf(file, "Thread #5 Sig21 WAIT\n");
        pthread_cond_wait(&Sig21, &M_Sig21);
        fprintf(file, "Thread #5 Sig21 GOTTEN\n");
        pthread_mutex_unlock(&M_Sig21);
        fprintf(file, "Thread #5 USED & MODIFIED\n");
        __sync_fetch_and_add(&long_1, 6);
        __sync_sub_and_fetch(&long_2, 8);
        __sync_val_compare_and_swap(&int_2, 2, 6);  
        if (pthread_mutex_trylock(&MCR1))
        {
            fprintf(file, "Thread #5 WAITING FOR MCR1\n");
            while (pthread_mutex_trylock(&MCR1))
            {
            }
        }
        while (is_empty())                                      
        {
            pthread_cond_wait(&not_empty, &MCR1);              
        }
        pop_back();                                             
        fprintf(file, "Thread #5 POP ELEM %d\n", getelem(0));   
        pthread_mutex_unlock(&MCR1);
        pthread_cond_broadcast(&not_full);                      
    }
    fprintf(file, "Thread #5 END\n");
}

void *p6_func(void *th)
{
    fprintf(file, "Thread #6 START\n");
    while (1)
    {
        pthread_mutex_lock(&M_Sig21);
        fprintf(file, "Thread #6 Sig21 WAIT\n");
        pthread_cond_wait(&Sig21, &M_Sig21);
        fprintf(file, "Thread #6 Sig21 GOTTEN\n");
        pthread_mutex_unlock(&M_Sig21);
        fprintf(file, "Thread #6 USED\n");
        __sync_nand_and_fetch(&unsigned_long_1, 10);
        pthread_mutex_lock(&M_Sig22);
        fprintf(file, "Thread #6 Sig22 WAIT\n");
        pthread_cond_wait(&Sig22, &M_Sig22);
        fprintf(file, "Thread #6 Sig22 GOTTEN\n");
        pthread_mutex_unlock(&M_Sig22);
        fprintf(file, "Thread #6 USED\n");
        __sync_fetch_and_nand(&unsigned_long_2, 10);
    }
    fprintf(file, "Thread #6 END\n");
}