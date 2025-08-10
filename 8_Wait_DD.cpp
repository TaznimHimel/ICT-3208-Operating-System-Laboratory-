#include <iostream>
#include <vector>
#include <list>

class Graph
{
private:
    int V;               // Number of vertices (processes)
    std::list<int> *adj; // Adjacency list representation

    // Recursive helper function for DFS-based cycle detection
    bool isCyclicUtil(int v, bool visited[], bool recursionStack[])
    {
        if (!visited[v])
        {
            // Mark the current node as visited and part of the recursion stack
            visited[v] = true;
            recursionStack[v] = true;

            // Recur for all the vertices adjacent to this vertex
            for (int neighbor : adj[v])
            {
                if (!visited[neighbor] && isCyclicUtil(neighbor, visited, recursionStack))
                {
                    return true; // Cycle found downstream
                }
                else if (recursionStack[neighbor])
                {
                    // If the neighbor is in the recursion stack, we have a back edge -> cycle found
                    return true;
                }
            }
        }
        // Remove the vertex from the recursion stack before returning
        recursionStack[v] = false;
        return false;
    }

public:
    Graph(int V)
    {
        this->V = V;
        adj = new std::list<int>[V];
    }

    ~Graph()
    {
        delete[] adj;
    }

    // Function to add an edge to the graph (Pi -> Pj)
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
    }

    // Main function to check if the graph contains a cycle
    bool hasCycle()
    {
        // Mark all the vertices as not visited and not part of recursion stack
        bool *visited = new bool[V];
        bool *recursionStack = new bool[V];
        for (int i = 0; i < V; i++)
        {
            visited[i] = false;
            recursionStack[i] = false;
        }

        // Call the recursive helper function to detect cycle in different DFS trees
        for (int i = 0; i < V; i++)
        {
            if (isCyclicUtil(i, visited, recursionStack))
            {
                delete[] visited;
                delete[] recursionStack;
                return true;
            }
        }

        delete[] visited;
        delete[] recursionStack;
        return false;
    }
};

int main()
{
    // Let's simulate the scenario from our explanation with 4 processes
    const int NUM_PROCESSES = 4;
    Graph g(NUM_PROCESSES);

    // Process IDs: P1=0, P2=1, P3=2, P4=3

    std::cout << "Constructing Wait-for Graph based on system state:" << std::endl;

    // P1 wants a resource held by P2 --> add edge P1 -> P2
    g.addEdge(0, 1);
    std::cout << "  - P1 is waiting for P2 (Edge: 0 -> 1)" << std::endl;

    // P2 wants a resource held by P3 --> add edge P2 -> P3
    g.addEdge(1, 2);
    std::cout << "  - P2 is waiting for P3 (Edge: 1 -> 2)" << std::endl;

    // P3 wants a resource held by P4 --> add edge P3 -> P4
    g.addEdge(2, 3);
    std::cout << "  - P3 is waiting for P4 (Edge: 2 -> 3)" << std::endl;

    // P4 wants a resource held by P1 --> add edge P4 -> P1
    g.addEdge(3, 0);
    std::cout << "  - P4 is waiting for P1 (Edge: 3 -> 0)" << std::endl;

    std::cout << "\nRunning deadlock detection algorithm..." << std::endl;

    if (g.hasCycle())
    {
        std::cout << "\nResult: Cycle detected. Deadlock confirmed in the system. 🚨" << std::endl;
    }
    else
    {
        std::cout << "\nResult: No cycle detected. The system is not in a deadlock state. ✅" << std::endl;
    }

    return 0;
}