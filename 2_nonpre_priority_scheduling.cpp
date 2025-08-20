#include <stdio.h>
#include <limits.h> // Used for INT_MAX

// A structure to represent a process
typedef struct
{
    int pid;             // Process ID
    int arrival_time;    // Arrival Time
    int burst_time;      // Burst Time
    int priority;        // Priority (lower number means higher priority)
    int is_completed;    // Flag to check if the process is completed
    int completion_time; // Time when the process completes
    int turnaround_time; // Turnaround Time = Completion Time - Arrival Time
    int waiting_time;    // Waiting Time = Turnaround Time - Burst Time
} Process;

int main()
{
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Array of process structures
    Process proc[n];

    printf("\nEnter process details (Arrival Time, Burst Time, Priority):\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d: ", i + 1);
        proc[i].pid = i + 1;
        scanf("%d %d %d", &proc[i].arrival_time, &proc[i].burst_time, &proc[i].priority);
        proc[i].is_completed = 0; // Initialize as not completed
    }

    int current_time = 0;
    int completed_processes = 0;
    float total_turnaround_time = 0;
    float total_waiting_time = 0;

    printf("\n--- Non-Preemptive Priority Scheduling ---\n");

    // Main scheduling loop continues until all processes are done
    while (completed_processes < n)
    {
        int highest_priority_index = -1;
        int highest_priority = INT_MAX;

        // Find the process with the highest priority among the arrived and uncompleted processes
        for (int i = 0; i < n; i++)
        {
            // Check if the process has arrived and is not yet completed
            if (proc[i].arrival_time <= current_time && proc[i].is_completed == 0)
            {
                // Check if its priority is higher than the current highest
                if (proc[i].priority < highest_priority)
                {
                    highest_priority = proc[i].priority;
                    highest_priority_index = i;
                }
                // If priorities are equal, use FCFS (First Come First Served) as a tie-breaker
                if (proc[i].priority == highest_priority)
                {
                    if (proc[i].arrival_time < proc[highest_priority_index].arrival_time)
                    {
                        highest_priority_index = i;
                    }
                }
            }
        }

        // If a process was found to execute
        if (highest_priority_index != -1)
        {
            Process *p = &proc[highest_priority_index];

            // Execute the process
            current_time += p->burst_time;

            // Calculate metrics
            p->completion_time = current_time;
            p->turnaround_time = p->completion_time - p->arrival_time;
            p->waiting_time = p->turnaround_time - p->burst_time;

            // Add to totals for averaging later
            total_turnaround_time += p->turnaround_time;
            total_waiting_time += p->waiting_time;

            // Mark process as completed
            p->is_completed = 1;
            completed_processes++;
        }
        else
        {
            // If no process has arrived yet, CPU is idle. Increment time.
            current_time++;
        }
    }

    // Print the final results table
    printf("\n------------------------------------------------------------------------------------------\n");
    printf("PID\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\n");
    printf("------------------------------------------------------------------------------------------\n");

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
    printf("------------------------------------------------------------------------------------------\n");

    // Print the average times
    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround_time / n);
    printf("Average Waiting Time:    %.2f\n", total_waiting_time / n);

    return 0;
}