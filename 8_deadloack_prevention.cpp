#include <stdio.h>

int main()
{
    int n, m;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int max[n][m], alloc[n][m], need[n][m], avail[m];

    // Input: Max
    printf("Enter Max Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    // Input: Allocation
    printf("Enter Allocation Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    // Input: Available
    printf("Enter Available Resources (%d):\n", m);
    for (int j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    // Compute Need = Max - Allocation
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
                // "Run" process i: it finishes and releases its allocation
                for (int j = 0; j < m; j++)
                    work[j] += alloc[i][j];
                finish[i] = 1;
                safeSeq[count++] = i;
                found = 1;
            }
        }
        if (!found)
            break; // no process could be satisfied -> unsafe
    }

    if (count == n)
    {
        printf("\nSystem is in a SAFE state.\nSafe Sequence: ");
        for (int k = 0; k < n; k++)
        {
            printf("P%d", safeSeq[k]);
            if (k != n - 1)
                printf(" -> ");
        }
        printf("\n");

        // Optional: show a step-by-step allocation simulation
        printf("\n--- Allocation Simulation in Safe Order ---\n");
        int simAvail[m];
        for (int j = 0; j < m; j++)
            simAvail[j] = avail[j];

        for (int idx = 0; idx < n; idx++)
        {
            int p = safeSeq[idx];
            // grant remaining need safely (conceptual)
            printf("Grant remaining need to P%d. It runs and finishes. ", p);
            // release allocation
            for (int j = 0; j < m; j++)
                simAvail[j] += alloc[p][j];
            printf("Available now: ");
            for (int j = 0; j < m; j++)
                printf("%d%s", simAvail[j], (j == m - 1) ? "\n" : " ");
        }
    }
    else
    {
        printf("\nSystem is UNSAFE (deadlock risk). No safe sequence exists with current state.\n");
    }

    return 0;
}
