#include <stdio.h>
#include <pthread.h>
#include<time.h>

#define NUM_THREADS 8

double local_sum[NUM_THREADS];
static long num_steps = 100000;

void *thread_proc(*void);

int main()
{
    int i;
    double x, sum = 0.0;
    double step = 1.0 / (double)num_steps;
    for (i = 0; i < num_steps; i++)
    {
        x = (i + 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }
    double pi = step * sum;
    printf("PI = %.10f\n", pi);
}

void *thread_proc(void *param)
{
    int idx = *(int*)param;

    for (int i = idx; )
}