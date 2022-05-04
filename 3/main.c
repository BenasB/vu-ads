// Benas Budrys 5 gr.

#include <stdio.h>
#include <time.h>
#include "pqueue.h"

#define BASIC_CUSTOMER 1
#define VIP_CUSTOMER 2 // MUST be bigger than BASIC
#define NO_CUSTOMER 0

struct Results
{
    int cashierDowntime;
    int cashierOvertime;
    int basicCustomerWaitingTime;
    int vipCustomerWaitingTime;
    int overallScore;
} processOneResults = {0, 0, 0, 0}, processTwoResults = {0, 0, 0, 0};
typedef struct Results Results;

struct Cashier
{
    int customer;
    int timeLeft;
};
typedef struct Cashier Cashier;

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

int areAllCashiersFree(Cashier cashiers[], int count)
{
    for (size_t i = 0; i < count; i++)
    {
        if (cashiers[i].customer != NO_CUSTOMER)
            return 0;
    }

    return 1;
}

void printProcessResults(Results *results, int processNo, int basicCustomerCount, int vipCustomerCount)
{
    printf("----- PROCESS %d -----\n", processNo);
    printf("Overall cashier downtime: %d, overtime: %d\n", results->cashierDowntime, results->cashierOvertime);

    double averageBasicCustomerWaitingTime = (results->basicCustomerWaitingTime * 1.0f) / basicCustomerCount;
    double averageVIPCustomerWaitingTime = (results->vipCustomerWaitingTime * 1.0f) / vipCustomerCount;
    printf("Average customer waiting time, BASIC: %lf, VIP: %lf\n", averageBasicCustomerWaitingTime, averageVIPCustomerWaitingTime);

    results->overallScore = results->cashierDowntime + 2 * results->cashierOvertime + 5 * averageBasicCustomerWaitingTime + 10 * averageVIPCustomerWaitingTime;
    printf("Process score (lower better): %d\n", results->overallScore);
}

void handleProcessOneCashier(Cashier *cashier, pqueue_t **queue, int *processOneBasicCustomersInQueue, int *processOneVIPCustomersInQueue)
{
    if (cashier->timeLeft > 0)
    {
        // Work
        cashier->timeLeft--;
    }

    if (cashier->timeLeft == 0)
    {
        // Free up a cashier
        cashier->customer = NO_CUSTOMER;
    }

    int error;
    if (cashier->customer == NO_CUSTOMER && !is_pq_empty(*queue, &error))
    {
        // Take a customer out of queue and assign to cashier
        int *customer = pq_pop(*queue, &error);
        cashier->customer = *customer;

        switch (*customer)
        {
        case BASIC_CUSTOMER:
            (*processOneBasicCustomersInQueue)--;
            cashier->timeLeft = basicSettings.serviceTime;
            break;

        case VIP_CUSTOMER:
            (*processOneVIPCustomersInQueue)--;
            cashier->timeLeft = vipSettings.serviceTime;
            break;
        }
    }

    if (cashier->customer == NO_CUSTOMER)
    {
        processOneResults.cashierDowntime++;
    }
}

void handleProcessTwoCashier(Cashier *cashier, pqueue_t **queue)
{
    if (cashier->timeLeft > 0)
    {
        // Work
        cashier->timeLeft--;
    }

    if (cashier->timeLeft == 0)
    {
        // Free up a cashier
        cashier->customer = NO_CUSTOMER;
    }

    int error;
    if (cashier->customer == NO_CUSTOMER && !is_pq_empty(*queue, &error))
    {
        // Take a customer out of queue and assign to cashier
        int *customer = pq_pop(*queue, &error);
        cashier->customer = *customer;
        cashier->timeLeft = *customer == VIP_CUSTOMER ? vipSettings.serviceTime : basicSettings.serviceTime;
    }

    if (cashier->customer == NO_CUSTOMER)
    {
        processTwoResults.cashierDowntime++;
    }
}

void mainCycle(int bankWorkingTime)
{
    int basicCustomerCount = 0;
    int vipCustomerCount = 0;
    int error;

    // Init process one
    pqueue_t *processOneQueue = create_pq(&error);
    int processOneCashierCount = basicSettings.cashierCount + vipSettings.cashierCount;
    int processOneBasicCustomersInQueue = 0;
    int processOneVIPCustomersInQueue = 0;
    Cashier processOneCashiers[processOneCashierCount];
    for (size_t i = 0; i < processOneCashierCount; i++)
    {
        Cashier emptyCashier = {NO_CUSTOMER, 0};
        processOneCashiers[i] = emptyCashier;
    }

    // Init process two
    pqueue_t *processTwoBasicQueue = create_pq(&error);
    pqueue_t *processTwoVIPQueue = create_pq(&error);
    Cashier processTwoBasicCashiers[basicSettings.cashierCount];
    for (size_t i = 0; i < basicSettings.cashierCount; i++)
    {
        Cashier emptyCashier = {NO_CUSTOMER, 0};
        processTwoBasicCashiers[i] = emptyCashier;
    }
    Cashier processTwoVIPCashiers[vipSettings.cashierCount];
    for (size_t i = 0; i < vipSettings.cashierCount; i++)
    {
        Cashier emptyCashier = {NO_CUSTOMER, 0};
        processTwoVIPCashiers[i] = emptyCashier;
    }

    // Working hours

    for (size_t i = 0; i < bankWorkingTime; i++)
    {
        int newCustomer = getRandomCustomer();

        if (newCustomer != NO_CUSTOMER)
        {
            switch (newCustomer)
            {
            case BASIC_CUSTOMER:
                basicCustomerCount++;
                processOneBasicCustomersInQueue++;
                break;

            case VIP_CUSTOMER:
                vipCustomerCount++;
                processOneVIPCustomersInQueue++;
                break;
            }

            // Queueing customers

            // Process 1
            pq_push(processOneQueue, &newCustomer, sizeof(newCustomer), newCustomer, &error);

            // Process 2
            pq_push(newCustomer == BASIC_CUSTOMER ? processTwoBasicQueue : processTwoVIPQueue, &newCustomer, sizeof(newCustomer), newCustomer, &error);
        }

        // Handle cashiers

        // Process 1
        for (size_t i = 0; i < processOneCashierCount; i++)
        {
            handleProcessOneCashier(&(processOneCashiers[i]), &processOneQueue, &processOneBasicCustomersInQueue, &processOneVIPCustomersInQueue);
        }
        processOneResults.basicCustomerWaitingTime += processOneBasicCustomersInQueue;
        processOneResults.vipCustomerWaitingTime += processOneVIPCustomersInQueue;

        // Process 2
        for (size_t i = 0; i < vipSettings.cashierCount; i++)
        {
            handleProcessTwoCashier(&(processTwoVIPCashiers[i]), &processTwoVIPQueue);
        }
        processTwoResults.vipCustomerWaitingTime += pq_elem_count(processTwoVIPQueue, &error);
        for (size_t i = 0; i < basicSettings.cashierCount; i++)
        {
            handleProcessTwoCashier(&(processTwoBasicCashiers[i]), &processTwoBasicQueue);
        }
        processTwoResults.basicCustomerWaitingTime += pq_elem_count(processTwoBasicQueue, &error);
    }

    // After working hours

    // Process 1
    while (!areAllCashiersFree(processOneCashiers, processOneCashierCount))
    {
        for (size_t i = 0; i < processOneCashierCount; i++)
        {
            handleProcessOneCashier(&(processOneCashiers[i]), &processOneQueue, &processOneBasicCustomersInQueue, &processOneVIPCustomersInQueue);
            processOneResults.cashierOvertime++;
        }
        processOneResults.basicCustomerWaitingTime += processOneBasicCustomersInQueue;
        processOneResults.vipCustomerWaitingTime += processOneVIPCustomersInQueue;
    }

    // Process 2
    while (!areAllCashiersFree(processTwoBasicCashiers, basicSettings.cashierCount) || !areAllCashiersFree(processTwoVIPCashiers, vipSettings.cashierCount))
    {
        for (size_t i = 0; i < vipSettings.cashierCount; i++)
        {
            handleProcessTwoCashier(&(processTwoVIPCashiers[i]), &processTwoVIPQueue);
            processTwoResults.cashierOvertime++;
        }
        processTwoResults.vipCustomerWaitingTime += pq_elem_count(processTwoVIPQueue, &error);
        for (size_t i = 0; i < basicSettings.cashierCount; i++)
        {
            handleProcessTwoCashier(&(processTwoBasicCashiers[i]), &processTwoBasicQueue);
            processTwoResults.cashierOvertime++;
        }
        processTwoResults.basicCustomerWaitingTime += pq_elem_count(processTwoBasicQueue, &error);
    }

    // Process 2

    // Cleanup
    free_pq(processOneQueue, &error);
    free_pq(processTwoBasicQueue, &error);
    free_pq(processTwoVIPQueue, &error);

    // Results
    int overallCustomerCount = basicCustomerCount + vipCustomerCount;
    printf("Served %d basic and %d VIP customers (%d overall)\n", basicCustomerCount, vipCustomerCount, overallCustomerCount);
    printProcessResults(&processOneResults, 1, basicCustomerCount, vipCustomerCount);
    printProcessResults(&processTwoResults, 2, basicCustomerCount, vipCustomerCount);
}

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("Input file does not exist");
        return -1;
    }

    fscanf(file, "%d %d", &basicSettings.customerChance, &vipSettings.customerChance);

    if (basicSettings.customerChance + vipSettings.customerChance > 100)
    {
        printf("Basic customer chance + VIP customer chance is more than 100\n");
        return -1;
    }

    fscanf(file, "%d %d", &basicSettings.cashierCount, &vipSettings.cashierCount);

    if (basicSettings.cashierCount <= 0)
    {
        printf("Basic cashier count must be above 0\n");
        return -1;
    }

    if (vipSettings.cashierCount <= 0)
    {
        printf("VIP cashier count must be above 0\n");
        return -1;
    }

    fscanf(file, "%d %d", &basicSettings.serviceTime, &vipSettings.serviceTime);

    int bankWorkingTime;

    fscanf(file, "%d", &bankWorkingTime);

    srand(time(0));

    mainCycle(bankWorkingTime);
}