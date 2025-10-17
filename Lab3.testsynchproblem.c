/*
Nandish Jha NAJ474 11282001
Part 1 - Barbershop Problem
*/



#include <stdio.h>
#include <standards.h>
#include <os.h>

/* extern variables from synchproblem.c */
extern int mutex;
extern int customer;
extern int barber;
extern int customerDone;
extern int barberDone;
extern int waiting;

/* function prototypes from synchproblem.c */
void Customer_proc(void *arg);
void Barber_proc(void *arg);

/* Configurations */
#define CHAIRS 5
#define CUSTOMERS 7
#define STACKSIZE 8192

int mainp(int argc, char **argv)
{
    PID b;
    PID c[CUSTOMERS];

    int i;

    mutex = NewSem(1);          /* binary semaphore for counter */
    customer = NewSem(0);       /* initially 0, barber waits */
    barber = NewSem(0);         /* initially 0, customer waits */
    customerDone = NewSem(0);   /* initially 0 */
    barberDone = NewSem(0);     /* initially 0 */

    /* create the parent process - barber */
    b = Create(Barber_proc, STACKSIZE,
        "Barber", NULL, NORM, USR);
    printf("Barber PID = %ld\n", b);

    /* create multiple child processes - customer */
    for (i = 0; i < CUSTOMERS; i++)
    {
        int idx = i;
        c[i] = Create(Customer_proc, STACKSIZE,
            "Customer", (void *)(long)idx, NORM, USR);
        printf("Customer %d PID = %ld\n", i, c[i]);
    }

    return 0;
}