#include <stdio.h>

int main()
{
    int n, m;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int max[n][m], alloc[n][m], need[n][m], avail[m];

    // Input Max Matrix
    printf("Enter Max Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    // Input Allocation Matrix
    printf("Enter Allocation Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    // Input Available Resources
    printf("Enter Available Resources (%d):\n", m);
    for (int j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    // Calculate Need Matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Safety Algorithm
    int finish[n];
    for (int i = 0; i < n; i++)
        finish[i] = 0;

    int work[m];
    for (int j = 0; j < m; j++)
        work[j] = avail[j];

    int safeSeq[n], count = 0;

    while (count < n)
    {
        int found = 0;
        for (int i = 0; i < n; i++)
        {
            if (finish[i])
                continue;

            int canRun = 1;
            for (int j = 0; j < m; j++)
            {
                if (need[i][j] > work[j])
                {
                    canRun = 0;
                    break;
                }
            }

            if (canRun)
            {
                for (int j = 0; j < m; j++)
                    work[j] += alloc[i][j]; // release resources after finish
                safeSeq[count++] = i;
                finish[i] = 1;
                found = 1;
            }
        }
        if (!found)
            break;
    }

    if (count == n)
    {
        printf("\n Deadlock Prevented! System is in a SAFE state.\n");
        printf("Safe Sequence: ");
        for (int k = 0; k < n; k++)
        {
            printf("P%d", safeSeq[k]);
            if (k != n - 1)
                printf(" -> ");
        }
        printf("\n");
    }
    else
    {
        printf("\n Deadlock Not Prevented! System is in an UNSAFE state.\n");
    }
    
    return 0;
}

/*
Processes: 3
Resources: 3

Max:
3 2 2
6 1 3
3 1 4

Allocation:
1 0 0
5 1 1
2 1 1

Available:
2 1 2
*/