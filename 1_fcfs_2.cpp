#include <stdio.h>

int main()
{
    int n, i, j, time = 0, completed = 0;
    int pid[10], at[10], bt[10];
    int ct[10], tat[10], wt[10];
    float avg_tat = 0, avg_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input PID, AT, BT
    for (i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        printf("Enter Arrival and Burst Time for P%d: ", pid[i]);
        scanf("%d %d", &at[i], &bt[i]);
    }

    // Copy original arrays to preserve input order
    int orig_pid[10], orig_at[10], orig_bt[10];
    for (i = 0; i < n; i++)
    {
        orig_pid[i] = pid[i];
        orig_at[i] = at[i];
        orig_bt[i] = bt[i];
    }

    // Sort by Arrival Time
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (at[i] > at[j])
            {
                int temp;
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }

    // Scheduling using while loop
    i = 0;
    time = 0;
    while (i < n)
    {
        if (time < at[i]) // CPU is idle, move time forward
        {
            time = at[i];
        }

        ct[i] = time + bt[i];   // Completion time
        tat[i] = ct[i] - at[i]; // Turnaround time
        wt[i] = tat[i] - bt[i]; // Waiting time
        time = ct[i];           // Update current time

        i++;
    }

    // Map results back to original PID order
    int orig_ct[10], orig_tat[10], orig_wt[10];
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (orig_pid[i] == pid[j])
            {
                orig_ct[i] = ct[j];
                orig_tat[i] = tat[j];
                orig_wt[i] = wt[j];
                avg_tat += orig_tat[i];
                avg_wt += orig_wt[i];
                break;
            }
        }
    }

    // Print output in original PID order
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               orig_pid[i], orig_at[i], orig_bt[i],
               orig_ct[i], orig_tat[i], orig_wt[i]);
    }

    printf("\nAverage Turnaround Time = %.2f", avg_tat / n);
    printf("\nAverage Waiting Time = %.2f\n", avg_wt / n);

    return 0;
}
