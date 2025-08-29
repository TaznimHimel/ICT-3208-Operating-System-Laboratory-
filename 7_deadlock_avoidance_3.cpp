#include <stdio.h>

int n, m;
int alloc[20][20], max[20][20], need[20][20], avail[20];

int isSafe()
{
    int work[20], finish[20], safeSeq[20];
    int count = 0, i, j;

    // Initialize work and finish arrays
    i = 0;
    while (i < m)
    {
        work[i] = avail[i];
        i++;
    }

    i = 0;
    while (i < n)
    {
        finish[i] = 0;
        i++;
    }

    count = 0;
    while (count < n)
    {
        int found = 0;
        i = 0;
        while (i < n)
        {
            if (!finish[i])
            {
                // Check if process i can execute
                int canExecute = 1;
                j = 0;
                while (j < m)
                {
                    if (need[i][j] > work[j])
                    {
                        canExecute = 0;
                        break;
                    }
                    j++;
                }

                if (canExecute)
                {
                    // Simulate execution
                    j = 0;
                    while (j < m)
                    {
                        work[j] += alloc[i][j];
                        j++;
                    }
                    finish[i] = 1;
                    safeSeq[count++] = i;
                    found = 1;
                }
            }
            i++;
        }

        if (!found)
        {
            printf("\nSystem is NOT in a safe state.\n");
            return 0;
        }
    }

    printf("\nSystem is in a SAFE state.\nSafe Sequence: ");
    i = 0;
    while (i < n)
    {
        printf("P%d", safeSeq[i]);
        if (i != n - 1)
            printf(" -> ");
        i++;
    }
    printf("\n");
    return 1;
}

int main()
{
    int i = 0, j = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix:\n");
    i = 0;
    while (i < n)
    {
        j = 0;
        while (j < m)
        {
            scanf("%d", &alloc[i][j]);
            j++;
        }
        i++;
    }

    printf("\nEnter Max Matrix:\n");
    i = 0;
    while (i < n)
    {
        j = 0;
        while (j < m)
        {
            scanf("%d", &max[i][j]);
            j++;
        }
        i++;
    }

    printf("\nEnter Available Resources:\n");
    i = 0;
    while (i < m)
    {
        scanf("%d", &avail[i]);
        i++;
    }

    // Calculate Need matrix
    i = 0;
    while (i < n)
    {
        j = 0;
        while (j < m)
        {
            need[i][j] = max[i][j] - alloc[i][j];
            j++;
        }
        i++;
    }

    printf("\nNeed Matrix:\n");
    i = 0;
    while (i < n)
    {
        j = 0;
        while (j < m)
        {
            printf("%d ", need[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }

    if (!isSafe())
    {
        return 0;
    }

    int reqProcess;
    printf("\nEnter the process number making a request (0-%d): ", n - 1);
    scanf("%d", &reqProcess);

    int request[20];
    printf("Enter request for each resource: ");
    i = 0;
    while (i < m)
    {
        scanf("%d", &request[i]);
        i++;
    }

    // Request <= Need
    i = 0;
    while (i < m)
    {
        if (request[i] > need[reqProcess][i])
        {
            printf("\nError: Process has exceeded its maximum claim.\n");
            return 0;
        }
        i++;
    }

    // Request <= Available
    i = 0;
    while (i < m)
    {
        if (request[i] > avail[i])
        {
            printf("\nResources not available. Process must wait.\n");
            return 0;
        }
        i++;
    }

    // Tentative allocation
    i = 0;
    while (i < m)
    {
        avail[i] -= request[i];
        alloc[reqProcess][i] += request[i];
        need[reqProcess][i] -= request[i];
        i++;
    }

    if (!isSafe())
    {
        printf("\nRequest cannot be granted (unsafe state).\n");
    }
    else
    {
        printf("\nRequest can be granted safely.\n");
    }

    return 0;
}
