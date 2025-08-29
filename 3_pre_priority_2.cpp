// Preemptive Priority Scheduling using while loops
#include <stdio.h>
#define MAX 30

int main()
{
    int n;
    int at[MAX], bt[MAX], pr[MAX], remaining_bt[MAX];
    int wt[MAX], tat[MAX], ct[MAX], pid[MAX];
    int completed[MAX] = {0};
    int time = 0, count = 0;

    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input priorities, arrival time, and burst time
    int i = 0;
    while (i < n)
    {
        pid[i] = i + 1;
        printf("Enter Priority, Arrival Time & Burst Time of process P%d: ", pid[i]);
        scanf("%d %d %d", &pr[i], &at[i], &bt[i]);
        remaining_bt[i] = bt[i];
        i++;
    }

    // Preemptive Priority Scheduling
    while (count < n)
    {
        int idx = -1;
        int mn_pr = 9999;

        i = 0;
        while (i < n)
        {
            if (at[i] <= time && !completed[i])
            {
                if (pr[i] < mn_pr)
                {
                    mn_pr = pr[i];
                    idx = i;
                }
                else if (pr[i] == mn_pr)
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
            remaining_bt[idx]--;
            time++;

            if (remaining_bt[idx] == 0)
            {
                completed[idx] = 1;
                count++;
                ct[idx] = time;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];
                total_wt += wt[idx];
                total_tat += tat[idx];
            }
        }
        else
        {
            time++; // CPU idle
        }
    }

    // Print results
    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
    i = 0;
    while (i < n)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], pr[i], ct[i], tat[i], wt[i]);
        i++;
    }

    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
