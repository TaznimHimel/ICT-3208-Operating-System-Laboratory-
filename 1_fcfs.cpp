#include <stdio.h>

struct Process
{
    int id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void find_times_fcfs(struct Process proc[], int n)
{
    int time = 0;
    for (int i = 0; i < n; i++)
    {
        if (time < proc[i].arrival_time)
        {
            // CPU idle until this process arrives
            time = proc[i].arrival_time;
        }
        time += proc[i].burst_time;
        proc[i].completion_time = time;
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
        proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
    }
}

void print_results(struct Process proc[], int n)
{
    float total_wt = 0, total_tat = 0;
    printf("\nP#\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        total_tat += proc[i].turnaround_time;
        total_wt += proc[i].waiting_time;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               proc[i].id,
               proc[i].arrival_time,
               proc[i].burst_time,
               proc[i].completion_time,
               proc[i].turnaround_time,
               proc[i].waiting_time);
    }
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);
}

void print_gantt_chart(struct Process proc[], int n)
{
    printf("\nGantt Chart:\n");

    // Top bar
    printf(" ");
    for (int i = 0; i < n; i++)
    {
        int segment = proc[i].burst_time;
        if (i > 0 && proc[i].arrival_time > proc[i - 1].completion_time)
        {
            segment += proc[i].arrival_time - proc[i - 1].completion_time; // idle time
        }
        for (int j = 0; j < segment; j++)
            printf("—");
        printf(" ");
    }
    printf("\n|");

    // Process/Idle IDs
    int time = 0;
    for (int i = 0; i < n; i++)
    {
        if (time < proc[i].arrival_time)
        {
            printf(" Idle |");
            time = proc[i].arrival_time;
        }
        printf(" P%d |", proc[i].id);
        time += proc[i].burst_time;
    }

    printf("\n ");
    for (int i = 0; i < n; i++)
    {
        int segment = proc[i].burst_time;
        if (i > 0 && proc[i].arrival_time > proc[i - 1].completion_time)
        {
            segment += proc[i].arrival_time - proc[i - 1].completion_time;
        }
        for (int j = 0; j < segment; j++)
            printf("—");
        printf(" ");
    }

    printf("\n");

    // Timeline
    time = 0;
    printf("%d", time);
    for (int i = 0; i < n; i++)
    {
        if (time < proc[i].arrival_time)
        {
            time = proc[i].arrival_time;
            printf("%*d", 6, time); // idle gap
        }
        time += proc[i].burst_time;
        printf("%*d", 6, time);
    }
    printf("\n");
}

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++)
    {
        proc[i].id = i + 1;
        printf("P%d Arrival Time: ", proc[i].id);
        scanf("%d", &proc[i].arrival_time);
        printf("P%d Burst Time: ", proc[i].id);
        scanf("%d", &proc[i].burst_time);
    }

    // Sort by Arrival Time (FCFS requirement)
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (proc[j].arrival_time > proc[j + 1].arrival_time)
            {
                struct Process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }

    find_times_fcfs(proc, n);
    print_results(proc, n);
    print_gantt_chart(proc, n);

    return 0;
}
