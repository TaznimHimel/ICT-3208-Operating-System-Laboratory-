// Non-preemptive Priority Scheduling using while loop
#include <stdio.h>
#define max 30

int main()
{
    int i, j, n;
    int bt[max], wt[max], tat[max], pr[max], at[max], ct[max], pid[max];
    int completed[max] = {0}; // flag to check if process is finished
    float awt = 0, atat = 0;
    int time = 0;  // current CPU time
    int count = 0; // Number of completed process

    // Enter number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input: Priority, Arrival time, Burst time
    i = 0;
    while (i < n)
    {
        pid[i] = i + 1;
        printf("Enter Priority, Arrival Time & Burst Time of process P%d: ", pid[i]);
        scanf("%d %d %d", &pr[i], &at[i], &bt[i]);
        i++;
    }

    // Non-preemptive Priority Scheduling
    while (count < n)
    {
        int idx = -1, min_pr = 9999;

        i = 0;
        while (i < n)
        {
            if (at[i] <= time && !completed[i])
            {
                if (pr[i] < min_pr)
                {
                    min_pr = pr[i];
                    idx = i;
                }
                else if (pr[i] == min_pr)
                {
                    if (idx == -1 || at[i] < at[idx])
                    {
                        idx = i;
                    }
                }
            }
            i++;
        }

        if (idx != -1)
        {
            time += bt[idx];
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            awt += wt[idx];
            atat += tat[idx];
            completed[idx] = 1;
            count++;
        }
        else
        {
            time++; // CPU idle
        }
    }

    // Output
    printf("\nP\tAT\tBT\tPR\tCT\tTAT\tWT");
    i = 0;
    while (i < n)
    {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d\t%d",
               pid[i], at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
        i++;
    }

    printf("\n\nAverage Waiting Time = %.2f", awt / n);
    printf("\nAverage Turnaround Time = %.2f\n", atat / n);

    return 0;
}
