#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // For INT_MAX
#include <string.h> // For memcpy

// A common structure to hold all process details for both algorithms
typedef struct
{
    int pid;             // Process ID
    int arrival_time;    // Arrival Time
    int burst_time;      // Original Burst Time
    int remaining_time;  // Remaining Time, used in SRTF
    int completion_time; // Completion Time
    int turnaround_time; // Turnaround Time
    int waiting_time;    // Waiting Time
    int is_completed;    // Flag for Non-Preemptive SJF
} Process;

/**
 * @brief Prints the final results table and average metrics for a given algorithm.
 * @param p Array of completed processes.
 * @param n Number of processes.
 * @param algorithm_name The name of the algorithm to display in the header.
 */
void printResults(Process p[], int n, const char *algorithm_name)
{
    float total_turnaround_time = 0;
    float total_waiting_time = 0;

    printf("\n--- %s Scheduling Results ---\n\n", algorithm_name);
    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    printf("---\t-------\t-----\t----------\t----------\t-------\n");

    for (int i = 0; i < n; i++)
    {
        // Find process with pid = i + 1 to print in a consistent order
        for (int j = 0; j < n; j++)
        {
            if (p[j].pid == i + 1)
            {
                printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
                       p[j].pid, p[j].arrival_time, p[j].burst_time,
                       p[j].completion_time, p[j].turnaround_time, p[j].waiting_time);

                total_turnaround_time += p[j].turnaround_time;
                total_waiting_time += p[j].waiting_time;
                break;
            }
        }
    }

    printf("\n--------------------------------------------------------\n");
    printf("Average Turnaround Time: %.2f ms\n", total_turnaround_time / n);
    printf("Average Waiting Time:    %.2f ms\n", total_waiting_time / n);
    printf("--------------------------------------------------------\n");
}

/**
 * @brief Simulates the Non-Preemptive SJF scheduling algorithm.
 * @param p Array of processes.
 * @param n Number of processes.
 */
void runNonPreemptiveSJF(Process p[], int n)
{
    int current_time = 0;
    int completed_processes = 0;

    while (completed_processes < n)
    {
        int shortest_job_index = -1;
        int min_burst_time = INT_MAX;

        // Find the shortest, arrived, uncompleted job
        for (int i = 0; i < n; i++)
        {
            if (p[i].arrival_time <= current_time && !p[i].is_completed)
            {
                if (p[i].burst_time < min_burst_time)
                {
                    min_burst_time = p[i].burst_time;
                    shortest_job_index = i;
                }
                else if (p[i].burst_time == min_burst_time && p[i].arrival_time < p[shortest_job_index].arrival_time)
                {
                    // Tie-break with arrival time
                    shortest_job_index = i;
                }
            }
        }

        if (shortest_job_index == -1)
        {
            current_time++; // CPU is idle
        }
        else
        {
            Process *current_p = &p[shortest_job_index];
            current_p->completion_time = current_time + current_p->burst_time;
            current_p->turnaround_time = current_p->completion_time - current_p->arrival_time;
            current_p->waiting_time = current_p->turnaround_time - current_p->burst_time;
            current_p->is_completed = 1;

            current_time = current_p->completion_time;
            completed_processes++;
        }
    }
    printResults(p, n, "Non-Preemptive SJF");
}

/**
 * @brief Simulates the Preemptive SJF (SRTF) scheduling algorithm.
 * @param p Array of processes.
 * @param n Number of processes.
 */
void runPreemptiveSJF(Process p[], int n)
{
    int current_time = 0;
    int completed_processes = 0;

    while (completed_processes < n)
    {
        int shortest_job_index = -1;
        int min_remaining_time = INT_MAX;

        // Find the job with the shortest remaining time that has arrived
        for (int i = 0; i < n; i++)
        {
            if (p[i].arrival_time <= current_time && p[i].remaining_time > 0)
            {
                if (p[i].remaining_time < min_remaining_time)
                {
                    min_remaining_time = p[i].remaining_time;
                    shortest_job_index = i;
                }
            }
        }

        if (shortest_job_index == -1)
        {
            current_time++; // CPU is idle
        }
        else
        {
            Process *current_p = &p[shortest_job_index];
            current_p->remaining_time--;
            current_time++;

            if (current_p->remaining_time == 0)
            {
                current_p->completion_time = current_time;
                current_p->turnaround_time = current_p->completion_time - current_p->arrival_time;
                current_p->waiting_time = current_p->turnaround_time - current_p->burst_time;
                completed_processes++;
            }
        }
    }
    printResults(p, n, "Preemptive SJF (SRTF)");
}

int main()
{
    int n, choice;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Number of processes must be positive.\n");
        return 1;
    }

    Process original_processes[n];

    // Get user input for each process
    for (int i = 0; i < n; i++)
    {
        original_processes[i].pid = i + 1;
        printf("\nEnter details for Process %d:\n", original_processes[i].pid);
        printf("  Arrival Time: ");
        scanf("%d", &original_processes[i].arrival_time);
        printf("  Burst Time: ");
        scanf("%d", &original_processes[i].burst_time);
    }

    printf("\nSelect the scheduling algorithm:\n");
    printf("1. Non-Preemptive SJF\n");
    printf("2. Preemptive SJF (SRTF)\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    // Create a temporary copy to run the simulation on,
    // preserving the original input data.
    Process temp_processes[n];
    memcpy(temp_processes, original_processes, n * sizeof(Process));

    switch (choice)
    {
    case 1:
        // Initialize fields for Non-Preemptive SJF
        for (int i = 0; i < n; i++)
            temp_processes[i].is_completed = 0;
        runNonPreemptiveSJF(temp_processes, n);
        break;
    case 2:
        // Initialize fields for Preemptive SJF
        for (int i = 0; i < n; i++)
            temp_processes[i].remaining_time = temp_processes[i].burst_time;
        runPreemptiveSJF(temp_processes, n);
        break;
    default:
        printf("Invalid choice!\n");
        break;
    }

    return 0;
}