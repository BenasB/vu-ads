#include <stdio.h>
#include <time.h>
#include "pqueue.h"

#define BASIC_CUSTOMER 0
#define VIP_CUSTOMER 1
#define NO_CUSTOMER -1

struct Settings
{
    int customerChance;
    int cashierCount;
    int serviceTime;
} basicSettings, vipSettings;

int getRandomCustomer()
{
    int randomNumber = rand() % 100;

    if (randomNumber >= 0 && randomNumber < basicSettings.customerChance)
        return BASIC_CUSTOMER;
    else if (randomNumber >= basicSettings.customerChance && randomNumber < basicSettings.customerChance + vipSettings.customerChance)
        return VIP_CUSTOMER;
    else
        return NO_CUSTOMER;
}

void mainIteration()
{
    int newCustomer = getRandomCustomer();
}

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("Input file does not exist");
        return -1;
    }

    fscanf(file, "%lf %lf", &basicSettings.customerChance, &vipSettings.customerChance);

    if (basicSettings.customerChance + vipSettings.customerChance > 1)
    {
        printf("Basic customer chance + VIP customer chance is more than one\n");
        return -1;
    }

    fscanf(file, "%d %d", &basicSettings.cashierCount, &vipSettings.cashierCount);
    fscanf(file, "%lf %lf", &basicSettings.serviceTime, &vipSettings.serviceTime);

    int bankWorkingTime;

    fscanf(file, "%d", bankWorkingTime);

    srand(time(0));

    for (size_t i = 0; i < bankWorkingTime; i++)
    {
        mainIteration();
    }
}