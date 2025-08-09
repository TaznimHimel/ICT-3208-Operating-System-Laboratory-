#include <stdio.h>

#define MAX 100

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
};

int main() {
    struct Process p[MAX];
    int n, time_quantum;
    int total_wt = 0, total_tat = 0;
    int completed = 0, current_time = 0;
    int queue[MAX], front = 0, rear = 0, visited[MAX] = {0};
    int gantt[MAX * 100], gantt_time[MAX * 100], gantt_index = 0; 

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nProcess %d\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &p[i].burst_time);
        p[i].remaining_time = p[i].burst_time;
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &time_quantum);

    // Sort by arrival time (important for RR with arrival times)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].arrival_time > p[j].arrival_time) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Initialize queue with first process
    queue[rear++] = 0;
    visited[0] = 1;
    current_time = p[0].arrival_time;

    while (completed < n) {
        int idx = queue[front++];
        
        // Gantt Chart logging
        gantt[gantt_index] = p[idx].id;
        gantt_time[gantt_index++] = current_time;

        if (p[idx].remaining_time <= time_quantum) {
            current_time += p[idx].remaining_time;
            p[idx].remaining_time = 0;
            p[idx].completion_time = current_time;
            completed++;
        } else {
            current_time += time_quantum;
            p[idx].remaining_time -= time_quantum;
        }

        // Add newly arrived processes to queue
        for (int i = 0; i < n; i++) {
            if (!visited[i] && p[i].arrival_time <= current_time && p[i].remaining_time > 0) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        // If current process still has time left, put it back in queue
        if (p[idx].remaining_time > 0) {
            queue[rear++] = idx;
        }

        // If queue is empty, jump to next arrival
        if (front == rear) {
            for (int i = 0; i < n; i++) {
                if (p[i].remaining_time > 0) {
                    queue[rear++] = i;
                    visited[i] = 1;
                    current_time = p[i].arrival_time;
                    break;
                }
            }
        }
    }

    // Calculate WT and TAT
    for (int i = 0; i < n; i++) {
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
    }

    // Output Table
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].id, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);
    }

    printf("\nAverage Waiting Time: %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_tat / n);

    // Gantt Chart Display
    printf("\nGantt Chart:\n");
    for (int i = 0; i < gantt_index; i++) {
        printf("| P%d ", gantt[i]);
    }
    printf("|\n");
    for (int i = 0; i < gantt_index; i++) {
        printf("%d    ", gantt_time[i]);
    }
    printf("%d\n", current_time);

    return 0;
}
