#include <stdio.h>

struct Process
{
    int id, at, bt, pr;
    int rt, ct, tat, wt, done;
};

void printGanttChart(int timeline[], int totalTime)
{
    printf("\nGantt Chart:\n");
    printf("Time: 0");
    int prev = timeline[0];
    for (int t = 0; t < totalTime; t++)
    {
        if (timeline[t] != prev)
        {
            printf(" -> P%d (%d)", prev, t);
            prev = timeline[t];
        }
    }
    printf(" -> P%d (%d)\n", prev, totalTime);
}

int nonPreemptive(struct Process p[], int n, int timeline[])
{
    int time = 0, completed = 0;
    while (completed < n)
    {
        int idx = -1, minPr = 9999;

        for (int i = 0; i < n; i++)
        {
            if (!p[i].done && p[i].at <= time)
            {
                if (p[i].pr < minPr)
                {
                    minPr = p[i].pr;
                    idx = i;
                }
                else if (p[i].pr == minPr && p[i].at < p[idx].at)
                {
                    idx = i;
                }
            }
        }

        if (idx != -1)
        {
            for (int t = 0; t < p[idx].bt; t++)
            {
                timeline[time + t] = p[idx].id;
            }
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].done = 1;
            completed++;
        }
        else
        {
            timeline[time] = 0; // idle
            time++;
        }
    }
    return time; // total time
}

int preemptive(struct Process p[], int n, int timeline[])
{
    int time = 0, completed = 0;
    while (completed < n)
    {
        int idx = -1, minPr = 9999;

        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= time && p[i].rt > 0)
            {
                if (p[i].pr < minPr)
                {
                    minPr = p[i].pr;
                    idx = i;
                }
                else if (p[i].pr == minPr && p[i].at < p[idx].at)
                {
                    idx = i;
                }
            }
        }

        if (idx != -1)
        {
            timeline[time] = p[idx].id;
            p[idx].rt--;
            if (p[idx].rt == 0)
            {
                completed++;
                p[idx].ct = time + 1;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
            }
        }
        else
        {
            timeline[time] = 0; // idle
        }
        time++;
    }
    return time; // total time
}

int main()
{
    int n, choice;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];

    for (int i = 0; i < n; i++)
    {
        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &p[i].at);
        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &p[i].bt);
        printf("P%d Priority: ", i + 1);
        scanf("%d", &p[i].pr);
        p[i].id = i + 1;
        p[i].done = 0;
        p[i].rt = p[i].bt;
    }

    printf("\nChoose Scheduling Type:\n");
    printf("1. Non-Preemptive Priority Scheduling\n");
    printf("2. Preemptive Priority Scheduling\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    int timeline[1000] = {0}; // store process at each time unit
    int totalTime = 0;

    if (choice == 1)
    {
        totalTime = nonPreemptive(p, n, timeline);
    }
    else if (choice == 2)
    {
        totalTime = preemptive(p, n, timeline);
    }
    else
    {
        printf("Invalid choice.\n");
        return 0;
    }

    printf("\nP\tAT\tBT\tPr\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].at, p[i].bt, p[i].pr,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printGanttChart(timeline, totalTime);

    return 0;
}
