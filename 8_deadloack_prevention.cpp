#include <stdio.h>
#include <stdbool.h>

// Define the number of processes and resources
#define NUM_PROCESSES 5
#define NUM_RESOURCES 3

// --- Function Prototypes ---
void calculate_need(int need[NUM_PROCESSES][NUM_RESOURCES], int max[NUM_PROCESSES][NUM_RESOURCES], int allocation[NUM_PROCESSES][NUM_RESOURCES]);
bool is_safe(int available[], int max[][NUM_RESOURCES], int allocation[][NUM_RESOURCES]);
void print_matrix(int matrix[NUM_PROCESSES][NUM_RESOURCES]);

int main()
{
    // Available instances of resources
    int available[NUM_RESOURCES] = {3, 3, 2};

    // Maximum resources that can be requested by each process
    int max[NUM_PROCESSES][NUM_RESOURCES] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}};

    // Resources currently allocated to each process
    int allocation[NUM_PROCESSES][NUM_RESOURCES] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}};

    // --- Initial State Check ---
    printf("### Checking Initial System State ###\n");
    is_safe(available, max, allocation);

    printf("\n----------------------------------------\n\n");

    // --- Resource Request Simulation ---
    printf("### Simulating Resource Request ###\n");
    int request_p = 1; // Process P1 is requesting
    int request[NUM_RESOURCES] = {1, 0, 2};

    printf("Process P%d requests resources (A, B, C): %d %d %d\n", request_p, request[0], request[1], request[2]);

    // Calculate need matrix for the check
    int need[NUM_PROCESSES][NUM_RESOURCES];
    calculate_need(need, max, allocation);

    // 1. Check if request <= need
    for (int i = 0; i < NUM_RESOURCES; i++)
    {
        if (request[i] > need[request_p][i])
        {
            printf("Error: Process has exceeded its maximum claim.\n");
            return 1; // Exit
        }
    }

    // 2. Check if request <= available
    for (int i = 0; i < NUM_RESOURCES; i++)
    {
        if (request[i] > available[i])
        {
            printf("Error: Resources not available for the request.\n");
            return 1; // Exit
        }
    }

    // 3. Pretend to allocate resources to check for safety
    int temp_available[NUM_RESOURCES];
    int temp_allocation[NUM_PROCESSES][NUM_RESOURCES];

    for (int i = 0; i < NUM_RESOURCES; i++)
    {
        temp_available[i] = available[i] - request[i];
        for (int p = 0; p < NUM_PROCESSES; p++)
        {
            temp_allocation[p][i] = allocation[p][i];
        }
        temp_allocation[request_p][i] += request[i];
    }

    printf("\nChecking if the new state would be safe...\n");
    if (is_safe(temp_available, max, temp_allocation))
    {
        printf("CONCLUSION: Request can be granted safely.\n");
    }
    else
    {
        printf("CONCLUSION: Request cannot be granted as it would lead to an unsafe state.\n");
    }

    return 0;
}

/**
 * Calculates the Need matrix.
 * Need = Max - Allocation
 */
void calculate_need(int need[NUM_PROCESSES][NUM_RESOURCES], int max[NUM_PROCESSES][NUM_RESOURCES], int allocation[NUM_PROCESSES][NUM_RESOURCES])
{
    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        for (int j = 0; j < NUM_RESOURCES; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

/**
 * Checks if the current system state is safe.
 */
bool is_safe(int available[], int max[][NUM_RESOURCES], int allocation[][NUM_RESOURCES])
{
    int need[NUM_PROCESSES][NUM_RESOURCES];
    calculate_need(need, max, allocation);

    // Work array, a copy of available resources
    int work[NUM_RESOURCES];
    for (int i = 0; i < NUM_RESOURCES; i++)
    {
        work[i] = available[i];
    }

    // Finish array to track completed processes
    bool finish[NUM_PROCESSES] = {0}; // All initialized to false

    int safe_sequence[NUM_PROCESSES];
    int count = 0;

    // Loop until all processes are finished or no more can be finished
    while (count < NUM_PROCESSES)
    {
        bool found = false;
        for (int p = 0; p < NUM_PROCESSES; p++)
        {
            // Find a process which is not finished and whose needs can be satisfied
            if (finish[p] == false)
            {
                int j;
                for (j = 0; j < NUM_RESOURCES; j++)
                {
                    if (need[p][j] > work[j])
                    {
                        break; // This process's needs are greater than available work
                    }
                }

                // If the inner loop completed, the process can run
                if (j == NUM_RESOURCES)
                {
                    // Add allocated resources of this process to work
                    for (int k = 0; k < NUM_RESOURCES; k++)
                    {
                        work[k] += allocation[p][k];
                    }
                    // Add process to safe sequence
                    safe_sequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        // If no process could be found in the entire iteration, the system is unsafe
        if (found == false)
        {
            printf("System is not in a safe state.\n");
            return false;
        }
    }

    // If we get here, the system is safe
    printf("System is in a safe state.\nSafe sequence: ");
    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        printf("P%d ", safe_sequence[i]);
    }
    printf("\n");
    return true;
}