/*
Nandish Jha NAJ474 11282001
Part 1 - Barbershop Problem
*/



#include<stdio.h>
#include<standards.h>
#include<os.h>

#define CHAIRS 5
#define CUSTOMERS 7
#define STACKSIZE 8192

/* my semaphores */
int mutex;
int barber;
int customer;
int barberDone;
int customerDone;

int waiting = 0;

/* prototypes */
void Customer_proc(void *arg);
void Barber_proc(void *arg);
int getHairCut(int id);
int balk(int id);
void cutHair();

void cutHair()
{
    printf("\t\tBarber is giving haircut\n");
    Sleep(5);
}

int getHairCut(int id)
{
    printf("\tCustomer %d is getting haircut\n", id);
    Sleep(5);
    return 0;
}

int balk(int id)
{
    printf("\tCustomer %d walking out of shop\n", id);
    return 0;
}

void Customer_proc(void *arg)
{
    int id = (int)(long)arg;

    P(mutex);
    if (waiting == CHAIRS) /* out of n chairs, if any left */
    {
        V(mutex);
        balk(id);
        return;
    }
    else
    {
        /* if that is not the case increment "waiting" */
        waiting++;
        V(mutex);
    }
    
    V(customer);
    P(barber);
    getHairCut(id);
    V(customerDone);
    P(barberDone);

    P(mutex);
    waiting--;
    V(mutex);
    Sleep(2);
}

void Barber_proc(void *arg)
{
    int i;

    for (i = 0; i < CUSTOMERS; i++)
    {
        P(customer);
        V(barber);
        cutHair();
        P(customerDone);
        V(barberDone);

        if (i == (CHAIRS - 1)) break;
    }

    printf("\nBarber finished all haircuts\n");
}