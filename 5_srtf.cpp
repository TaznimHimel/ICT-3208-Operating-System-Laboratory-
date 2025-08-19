#include <stdio.h>
#include <limits.h> // Used for INT_MAX

// A structure to represent a process
typedef struct
{
    int pid;          // Process ID
    int arrival_time; // Arrival Time
    int burst_time;   // Original Burst Time

    int remaining_time; // Remaining time to execute
    int is_started;     // Flag to calculate response time once

    int completion_time; // Time when the process completes
    int turnaround_time; // Turnaround Time = Completion - Arrival
    int waiting_time;    // Waiting Time = Turnaround - Burst
    int response_time;   // Response Time = First Run - Arrival
} Process;

int main()
{
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Array of process structures
    Process proc[n];

    printf("\nEnter process details (Arrival Time and Burst Time):\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d: ", i + 1);
        proc[i].pid = i + 1;
        scanf("%d %d", &proc[i].arrival_time, &proc[i].burst_time);

        // Initialize runtime variables
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].is_started = 0;
    }

    int current_time = 0;
    int completed_processes = 0;
    float total_turnaround_time = 0;
    float total_waiting_time = 0;
    float total_response_time = 0;

    printf("\n--- Shortest Remaining Time First (SRTF) Scheduling ---\n");

    // Main simulation loop continues until all processes are done
    while (completed_processes < n)
    {
        int shortest_job_index = -1;
        int min_remaining_time = INT_MAX;

        // Find the process with the minimum remaining time among the arrived processes
        for (int i = 0; i < n; i++)
        {
            if (proc[i].arrival_time <= current_time && proc[i].remaining_time > 0)
            {
                if (proc[i].remaining_time < min_remaining_time)
                {
                    min_remaining_time = proc[i].remaining_time;
                    shortest_job_index = i;
                }
                // Tie-breaker: If remaining times are equal, choose the one that arrived first
                if (proc[i].remaining_time == min_remaining_time)
                {
                    if (proc[i].arrival_time < proc[shortest_job_index].arrival_time)
                    {
                        shortest_job_index = i;
                    }
                }
            }
        }

        // If a process was found to execute
        if (shortest_job_index != -1)
        {
            Process *p = &proc[shortest_job_index];

            // Calculate response time if it's the process's first time running
            if (p->is_started == 0)
            {
                p->response_time = current_time - p->arrival_time;
                p->is_started = 1;
            }

            // Execute the process for one time unit
            p->remaining_time--;

            // Check if the process has completed
            if (p->remaining_time == 0)
            {
                p->completion_time = current_time + 1;
                completed_processes++;
            }
        }

        // Advance the simulation time
        current_time++;
    }

    // Calculate TAT and WT for all processes
    for (int i = 0; i < n; i++)
    {
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
        proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;

        total_turnaround_time += proc[i].turnaround_time;
        total_waiting_time += proc[i].waiting_time;
        total_response_time += proc[i].response_time;
    }

    // Print the final results table
    printf("\n------------------------------------------------------------------------------------------\n");
    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\t\tResponse\n");
    printf("------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].pid,
               proc[i].arrival_time,
               proc[i].burst_time,
               proc[i].completion_time,
               proc[i].turnaround_time,
               proc[i].waiting_time,
               proc[i].response_time);
    }
    printf("------------------------------------------------------------------------------------------\n");

    // Print the average times
    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround_time / n);
    printf("Average Waiting Time:    %.2f\n", total_waiting_time / n);
    printf("Average Response Time:   %.2f\n", total_response_time / n);

    return 0;
}