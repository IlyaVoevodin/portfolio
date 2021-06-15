#include "thread.h"

int main()
{
    file = fopen("pro.log", "wt");
    sem_init(&SCR21, 0, 0);
    pthread_cond_init(&not_empty, NULL);
    pthread_cond_init(&not_full, NULL);
    pthread_create(&p1, NULL, p1_func, NULL);
    pthread_create(&p2, NULL, p2_func, NULL);
    pthread_create(&p3, NULL, p3_func, NULL);
    pthread_create(&p4, NULL, p4_func, NULL);
    pthread_create(&p5, NULL, p5_func, NULL);
    pthread_create(&p6, NULL, p6_func, NULL);
    pthread_join(p3, NULL);
    fprintf(file, "DONE");
    fclose(file);
    return 0;
}
