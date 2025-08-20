#include <stdio.h>
#include <limits.h> // Used for INT_MAX

// A simplified structure to represent a process
typedef struct
{
    int pid;             // Process ID
    int arrival_time;    // Arrival Time
    int burst_time;      // Original Burst Time
    int priority;        // Priority (lower number is higher priority)
    int remaining_time;  // Remaining time to execute
    int completion_time; // Time when the process completes
    int turnaround_time; // Completion Time - Arrival Time
    int waiting_time;    // Turnaround Time - Burst Time
} Process;

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process proc[n]; // Array of process structures

    // --- Input Process Details ---
    printf("\nEnter process details (Arrival Time, Burst Time, Priority):\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d: ", i + 1);
        proc[i].pid = i + 1;
        scanf("%d %d %d", &proc[i].arrival_time, &proc[i].burst_time, &proc[i].priority);
        proc[i].remaining_time = proc[i].burst_time; // Initially, remaining time is the full burst time
    }

    int current_time = 0;
    int completed_processes = 0;
    float total_turnaround_time = 0;
    float total_waiting_time = 0;

    printf("\n--- Preemptive Priority Scheduling Simulation ---\n");

    // --- Main Simulation Loop ---
    // The loop continues until all processes are completed.
    while (completed_processes < n)
    {
        int highest_priority_index = -1;

        // Find the process with the highest priority among those that have arrived and are not yet finished.
        for (int i = 0; i < n; i++)
        {
            if (proc[i].arrival_time <= current_time && proc[i].remaining_time > 0)
            {
                // A new process is chosen if:
                // 1. It's the first one we've found in this time slice.
                // 2. Its priority is higher (lower number) than the one we've already chosen.
                // 3. It has the same priority, but it arrived earlier (tie-breaker).
                if (highest_priority_index == -1 ||
                    proc[i].priority < proc[highest_priority_index].priority ||
                    (proc[i].priority == proc[highest_priority_index].priority && proc[i].arrival_time < proc[highest_priority_index].arrival_time))
                {
                    highest_priority_index = i;
                }
            }
        }

        // If no process is ready to run, the CPU is idle. We just advance the time.
        if (highest_priority_index == -1)
        {
            current_time++;
            continue;
        }

        // Execute the selected process for one time unit.
        proc[highest_priority_index].remaining_time--;

        // Check if the process has completed its execution.
        if (proc[highest_priority_index].remaining_time == 0)
        {
            // Calculate performance metrics for the completed process
            proc[highest_priority_index].completion_time = current_time + 1;
            proc[highest_priority_index].turnaround_time = proc[highest_priority_index].completion_time - proc[highest_priority_index].arrival_time;
            proc[highest_priority_index].waiting_time = proc[highest_priority_index].turnaround_time - proc[highest_priority_index].burst_time;

            // Add to totals for final average calculation
            total_turnaround_time += proc[highest_priority_index].turnaround_time;
            total_waiting_time += proc[highest_priority_index].waiting_time;

            completed_processes++;
        }

        // Advance simulation time by one unit.
        current_time++;
    }

    // --- Output Results ---
    printf("\n----------------------------------------------------------------------------------\n");
    printf("PID\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\n");
    printf("----------------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].pid,
               proc[i].arrival_time,
               proc[i].burst_time,
               proc[i].priority,
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