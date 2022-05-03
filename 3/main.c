#include <stdio.h>
#include "pqueue.h"

struct Settings
{
    double customerChance;
    int cashierCount;
    int serviceTime;
} basicSettings, vipSettings;

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("Input file does not exist");
        return -1;
    }

    fscanf(file, "%lf %lf", &basicSettings.customerChance, &vipSettings.customerChance);

    double noCustomerChance = 1 - basicSettings.customerChance - vipSettings.customerChance;

    if (noCustomerChance < 0)
    {
        printf("Basic customer chance + VIP customer chance is more than one\n");
        return -1;
    }

    fscanf(file, "%d %d", &basicSettings.cashierCount, &vipSettings.cashierCount);
    fscanf(file, "%lf %lf", &basicSettings.serviceTime, &vipSettings.serviceTime);

    int bankWorkingTime;

    fscanf(file, "%d", bankWorkingTime);
}