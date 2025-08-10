#include <stdio.h>
#include <stdbool.h>

// Let's define our components
#define NUM_PROCESSES 2
#define NUM_RESOURCES 2

// Total nodes in the graph = P1, P2, R1, R2
#define TOTAL_NODES (NUM_PROCESSES + NUM_RESOURCES)

// Node IDs for clarity
#define P1 0
#define P2 1
#define R1 2
#define R2 3

// Adjacency matrix to represent the graph. graph[i][j] = 1 means edge i->j
int graph[TOTAL_NODES][TOTAL_NODES] = {0};

/**
 * A placeholder for a real cycle detection algorithm (like DFS).
 * This is the complex part of the implementation.
 * @param current_graph The graph state to check.
 * @return true if a cycle is detected, false otherwise.
 */
bool has_cycle(int current_graph[TOTAL_NODES][TOTAL_NODES])
{
    // A full implementation of Depth-First Search (DFS) would go here
    // to detect back edges in the graph, which indicate cycles.
    // For this example, we will manually return results based on our simulation.

    // Manual check for the specific cycle in our simulation: P1->R2->P2->R1->P1
    if (current_graph[P1][R2] && current_graph[R2][P2] && current_graph[P2][R1] && current_graph[R1][P1])
    {
        return true;
    }
    return false;
}

/**
 * The main logic for handling a resource request.
 * @param p The process making the request (e.g., P1).
 * @param r The resource being requested (e.g., R1).
 */
void handle_request(int p_id, int r_id)
{
    printf("--- P%d requests R%d ---\n", p_id + 1, r_id - NUM_PROCESSES + 1);

    // 1. Add the request edge to the graph
    // (In a real system, this would change a CLAIM edge to a REQUEST edge)
    printf("Adding request edge: P%d -> R%d\n", p_id + 1, r_id - NUM_PROCESSES + 1);
    graph[p_id][r_id] = 1;

    // 2. Check if granting the request is safe by checking for a cycle
    // We create a temporary graph where the request is granted
    int temp_graph[TOTAL_NODES][TOTAL_NODES];
    for (int i = 0; i < TOTAL_NODES; i++)
    {
        for (int j = 0; j < TOTAL_NODES; j++)
        {
            temp_graph[i][j] = graph[i][j];
        }
    }

    // Pretend to grant: Convert request P->R to assignment R->P
    temp_graph[p_id][r_id] = 0; // Remove request edge
    temp_graph[r_id][p_id] = 1; // Add assignment edge

    printf("Checking for cycle if request is granted...\n");
    if (has_cycle(temp_graph))
    {
        printf("RESULT: UNSAFE. Granting request would create a cycle. Request for R%d denied.\n\n", r_id - NUM_PROCESSES + 1);
        // The request edge P->R remains, and the process must wait.
    }
    else
    {
        printf("RESULT: SAFE. Request for R%d can be granted.\n\n", r_id - NUM_PROCESSES + 1);
        // Update the real graph
        graph[p_id][r_id] = 0; // Remove request
        graph[r_id][p_id] = 1; // Add assignment
    }
}

int main()
{
    printf("--- Simulation Start ---\n");
    // This graph is initially empty, representing the state before any requests or grants.

    // Step 1: P1 requests R1 (safe)
    handle_request(P1, R1);

    // Step 2: P2 requests R2 (safe)
    handle_request(P2, R2);

    // Step 3: P1 requests R2 (P1 must wait)
    handle_request(P1, R2);

    // Step 4: P2 requests R1 (unsafe - this would create the deadlock cycle)
    // The handle_request function will now use our manual has_cycle logic.
    handle_request(P2, R1);

    return 0;
}