#include <stdio.h>
#include <stdbool.h>

// Define the number of processes and resources
#define NUM_PROCESSES 5
#define NUM_RESOURCES 3

// Function to calculate the need matrix
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

// Function to check if the system is in a safe state
bool is_safe(int processes[], int available[], int max[][NUM_RESOURCES], int allocation[][NUM_RESOURCES], int need[][NUM_RESOURCES])
{
    int work[NUM_RESOURCES];
    for (int i = 0; i < NUM_RESOURCES; i++)
    {
        work[i] = available[i];
    }

    bool finish[NUM_PROCESSES] = {0}; // All initialized to false
    int safe_sequence[NUM_PROCESSES];
    int count = 0;

    while (count < NUM_PROCESSES)
    {
        bool found = false;
        for (int p = 0; p < NUM_PROCESSES; p++)
        {
            if (finish[p] == false)
            {
                int j;
                for (j = 0; j < NUM_RESOURCES; j++)
                {
                    if (need[p][j] > work[j])
                    {
                        break;
                    }
                }

                if (j == NUM_RESOURCES)
                { // If need <= work for all resources
                    for (int k = 0; k < NUM_RESOURCES; k++)
                    {
                        work[k] += allocation[p][k];
                    }
                    safe_sequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        if (found == false)
        {
            printf("System is not in a safe state.\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < NUM_PROCESSES; i++)
    {
        printf("P%d ", safe_sequence[i]);
    }
    printf("\n");
    return true;
}

int main()
{
    int processes[] = {0, 1, 2, 3, 4};

    // Available instances of resources
    int available[NUM_RESOURCES] = {3, 3, 2};

    // Maximum R that can be requested by each process
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

    int need[NUM_PROCESSES][NUM_RESOURCES];
    calculate_need(need, max, allocation);

    // Check if the initial system state is safe
    printf("### Checking Initial System State ###\n");
    is_safe(processes, available, max, allocation, need);

    printf("\n----------------------------------------\n\n");

    // --- Resource Request Simulation ---
    printf("### Simulating Resource Request ###\n");
    int request_p = 1; // Process P1 is requesting
    int request[NUM_RESOURCES] = {1, 0, 2};
    printf("Process P%d requests resources: ", request_p);
    for (int i = 0; i < NUM_RESOURCES; i++)
        printf("%d ", request[i]);
    printf("\n");

    // 1. Check if request <= need
    bool valid_request = true;
    for (int i = 0; i < NUM_RESOURCES; i++)
    {
        if (request[i] > need[request_p][i])
        {
            valid_request = false;
            break;
        }
    }

    if (valid_request)
    {
        // 2. Check if request <= available
        for (int i = 0; i < NUM_RESOURCES; i++)
        {
            if (request[i] > available[i])
            {
                valid_request = false;
                break;
            }
        }

        if (valid_request)
        {
            // Pretend to allocate resources
            for (int i = 0; i < NUM_RESOURCES; i++)
            {
                available[i] -= request[i];
                allocation[request_p][i] += request[i];
                need[request_p][i] -= request[i];
            }

            // 3. Check if the new state is safe
            if (is_safe(processes, available, max, allocation, need))
            {
                printf("Request can be granted.\n");
            }
            else
            {
                printf("Request cannot be granted as it leads to an unsafe state.\n");
                // Rollback the changes (optional, as the program ends here)
            }
        }
        else
        {
            printf("Request cannot be granted. Resources not available.\n");
        }
    }
    else
    {
        printf("Request cannot be granted. Process has exceeded its maximum claim.\n");
    }

    return 0;
}