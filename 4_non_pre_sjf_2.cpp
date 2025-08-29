#include <stdio.h>

#define MAX 20

int main()
{
    int n, i, idx;
    int pid[MAX], at[MAX], bt[MAX], ct[MAX], tat[MAX], wt[MAX], completed[MAX] = {0};
    int time = 0, count = 0;
    float avg_tat = 0, avg_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // input arrival time & burst time
    i = 0;
    while (i < n)
    {
        pid[i] = i + 1;
        printf("Enter Arrival Times & Burst Times of process p%d :", pid[i]);
        scanf("%d %d", &at[i], &bt[i]);
        i++;
    }

    // scheduling
    while (count < n)
    {
        idx = -1;
        int min_bt = 9999;

        i = 0;
        while (i < n)
        {
            if (at[i] <= time && !completed[i])
            {
                if (bt[i] < min_bt)
                {
                    min_bt = bt[i];
                    idx = i;
                }
                else if (bt[i] == min_bt)
                {
                    if (at[i] < at[idx])
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

            avg_tat += tat[idx];
            avg_wt += wt[idx];

            completed[idx] = 1;
            count++;
        }
        else
        {
            time++; // CPU idle
        }
    }

    // print result
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    i = 0;
    while (i < n)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
        i++;
    }

    printf("\nAverage Turnaround Time: %.2f", avg_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", avg_wt / n);

    return 0;
}
