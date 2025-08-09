#include <stdio.h>
#include <stdlib.h>

// A structure to hold process details
typedef struct
{
    int pid;             // Process ID
    int arrival_time;    // Arrival Time
    int burst_time;      // Burst Time
    int completion_time; // Completion Time
    int turnaround_time; // Turnaround Time
    int waiting_time;    // Waiting Time
} Process;

/**
 * @brief Sorts processes based on arrival time using Bubble Sort.
 * @param p Array of processes.
 * @param n Number of processes.
 */
void sortByArrival(Process p[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].arrival_time > p[j + 1].arrival_time)
            {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

/**
 * @brief Calculates all timing metrics for each process.
 * @param p Array of processes.
 * @param n Number of processes.
 */
void calculateMetrics(Process p[], int n)
{
    int current_time = 0;

    // The first process's completion time depends on its arrival.
    // The CPU might be idle before the first process arrives.
    current_time = p[0].arrival_time;

    for (int i = 0; i < n; i++)
    {
        // If the current process arrives after the previous one has finished,
        // the CPU will be idle. The start time is its arrival time.
        if (p[i].arrival_time > current_time)
        {
            current_time = p[i].arrival_time;
        }

        // Calculate metrics for the current process
        p[i].completion_time = current_time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;

        // The next process can only start after the current one completes
        current_time = p[i].completion_time;
    }
}

/**
 * @brief Prints the final results table and average metrics.
 * @param p Array of processes.
 * @param n Number of processes.
 */
void printResults(Process p[], int n)
{
    float total_turnaround_time = 0;
    float total_waiting_time = 0;

    printf("\n--- FCFS Scheduling Results ---\n\n");
    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    printf("---\t-------\t-----\t----------\t----------\t-------\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               p[i].pid,
               p[i].arrival_time,
               p[i].burst_time,
               p[i].completion_time,
               p[i].turnaround_time,
               p[i].waiting_time);

        total_turnaround_time += p[i].turnaround_time;
        total_waiting_time += p[i].waiting_time;
    }

    printf("\n--------------------------------------------------------\n");
    printf("Average Turnaround Time: %.2f ms\n", total_turnaround_time / n);
    printf("Average Waiting Time:    %.2f ms\n", total_waiting_time / n);
    printf("--------------------------------------------------------\n");
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Number of processes must be positive.\n");
        return 1;
    }

    // Array of Process structures
    Process processes[n];

    // Get user input for each process
    for (int i = 0; i < n; i++)
    {
        processes[i].pid = i + 1;
        printf("\nEnter details for Process %d:\n", processes[i].pid);
        printf("  Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("  Burst Time: ");
        scanf("%d", &processes[i].burst_time);
    }

    // 1. Sort processes by arrival time
    sortByArrival(processes, n);

    // 2. Calculate completion, turnaround, and waiting times
    calculateMetrics(processes, n);

    // 3. Print the final results
    printResults(processes, n);

    return 0;
}