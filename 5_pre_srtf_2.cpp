#include <stdio.h>
#define MAX 20

int main()
{
    int n, i, time = 0, count = 0;
    int pid[MAX], at[MAX], bt[MAX], rem_bt[MAX], ct[MAX], tat[MAX], wt[MAX];
    int completed[MAX] = {0};
    float avg_tat = 0, avg_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input processes
    for (i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        printf("Enter Arrival Time & Burst Time of process P%d: ", pid[i]);
        scanf("%d %d", &at[i], &bt[i]);
        rem_bt[i] = bt[i];
    }

    // Simulation loop (runs until all processes are completed)
    while (count < n)
    {
        int idx = -1;
        int min_rem = 9999;

        // Pick process with minimum remaining time
        for (i = 0; i < n; i++)
        {
            if (at[i] <= time && !completed[i])
            {
                if (rem_bt[i] < min_rem && rem_bt[i] > 0)
                {
                    min_rem = rem_bt[i];
                    idx = i;
                }
                else if (rem_bt[i] == min_rem && idx != -1)
                {
                    if (at[i] < at[idx])
                        idx = i;
                }
            }
        }

        if (idx != -1)
        {
            rem_bt[idx]--; // Run for 1 time unit
            time++;

            // If process finishes
            if (rem_bt[idx] == 0)
            {
                ct[idx] = time;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];

                avg_tat += tat[idx];
                avg_wt += wt[idx];

                completed[idx] = 1;
                count++;
            }
        }
        else
        {
            // CPU idle
            time++;
        }
    }

    // Output results
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time: %.2f", avg_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", avg_wt / n);

    return 0;
}
