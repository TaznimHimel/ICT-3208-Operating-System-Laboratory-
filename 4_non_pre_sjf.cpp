#include <stdio.h>
#include <limits.h> // Used for INT_MAX

// A simplified structure to represent a process
typedef struct
{
    int pid;             // Process ID
    int arrival_time;    // Arrival Time
    int burst_time;      // CPU Burst Time
    int completion_time; // Time when the process completes
    int turnaround_time; // Completion Time - Arrival Time
    int waiting_time;    // Turnaround Time - Burst Time
} Process;

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process proc[n];
    int is_completed[n]; // Array to track completion status

    // --- Input Process Details ---
    printf("\nEnter process details (Arrival Time and Burst Time):\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d: ", i + 1);
        proc[i].pid = i + 1;
        scanf("%d %d", &proc[i].arrival_time, &proc[i].burst_time);
        is_completed[i] = 0; // Initialize all processes as not completed
    }

    int current_time = 0;
    int completed_processes = 0;
    float total_turnaround_time = 0;
    float total_waiting_time = 0;

    printf("\n--- Shortest Job First (SJF) Scheduling ---\n");

    // --- Main Simulation Loop ---
    // The loop continues until all processes are completed.
    while (completed_processes < n)
    {
        int shortest_job_index = -1;

        // Find the shortest, uncompleted job that has arrived.
        for (int i = 0; i < n; i++)
        {
            if (proc[i].arrival_time <= current_time && !is_completed[i])
            {
                // A new process is chosen if:
                // 1. It's the first available one we've found.
                // 2. Its burst time is shorter than the current shortest.
                // 3. It has the same burst time, but it arrived earlier (tie-breaker).
                if (shortest_job_index == -1 ||
                    proc[i].burst_time < proc[shortest_job_index].burst_time ||
                    (proc[i].burst_time == proc[shortest_job_index].burst_time && proc[i].arrival_time < proc[shortest_job_index].arrival_time))
                {
                    shortest_job_index = i;
                }
            }
        }

        // If no process is ready, the CPU is idle. Advance time.
        if (shortest_job_index == -1)
        {
            current_time++;
        }
        else // A process is ready to be executed
        {
            // Since SJF is non-preemptive, the process runs to completion.
            // Advance current_time by the entire burst time of the selected process.
            current_time += proc[shortest_job_index].burst_time;

            // Calculate metrics for the completed process
            proc[shortest_job_index].completion_time = current_time;
            proc[shortest_job_index].turnaround_time = proc[shortest_job_index].completion_time - proc[shortest_job_index].arrival_time;
            proc[shortest_job_index].waiting_time = proc[shortest_job_index].turnaround_time - proc[shortest_job_index].burst_time;

            // Add to totals for final average calculation
            total_turnaround_time += proc[shortest_job_index].turnaround_time;
            total_waiting_time += proc[shortest_job_index].waiting_time;

            // Mark the process as completed
            is_completed[shortest_job_index] = 1;
            completed_processes++;
        }
    }

    // --- Output Results ---
    printf("\n----------------------------------------------------------------------------------\n");
    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    printf("----------------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               proc[i].pid,
               proc[i].arrival_time,
               proc[i].burst_time,
               proc[i].completion_time,
               proc[i].turnaround_time,
               proc[i].waiting_time);
    }
    printf("----------------------------------------------------------------------------------\n");

    // Print the final average times
    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround_time / n);
    printf("Average Waiting Time:    %.2f\n", total_waiting_time / n);

    return 0;
}