#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
// Prims alogrithm - minimum spanning tree
// Shortest path taken without cycles
void prim(int n, int** cost) {
    int i, j, u, v, min, mincost = 0;
    int* visited= (int*)calloc(n,sizeof(int));
    int* parent = (int*)calloc(n,sizeof(int));

    // Initialize visited and parent arrays
    for (i = 0; i < n; i++) {
        visited[i] = 0; //not visited
        parent[i] = -1; //not anynodes parent
    }

    // Mark the starting vertex as visited
    visited[0] = 1;

    // Find the minimum edge cost and update parent and visited arrays
    for (i = 1; i < n; i++) { //i!=0 because i = 0 is the starting vertex
        min = INT_MAX;
        for (j = 0; j < n; j++) {
            if (visited[j]) {
                for (int k = 0; k < n; k++) {//for each node find the minimum non-visted vertex
                    if (cost[j][k] == 0) continue;
                    if (!visited[k] && cost[j][k] < min) {
                        min = cost[j][k];
                        u = j;//store index of minimum edge cost in u , v
                        v = k;
                    }
                }
            }
        }
        
        visited[v] = 1; //now set final node to confirm as visited
        parent[v] = u; //note down parent of current node
        mincost += min; // minimum cost is updated
    }

    // Print the minimum spanning tree
    printf("Edges in the minimum spanning tree:\n");
    for (i = 1; i < n; i++) {
        printf("%d - %d\n", parent[i], i);
    }
    printf("Cost of minimum spanning tree = %d\n", mincost);
}

int main() {
    int n, i, j;

    printf("Enter the number of nodes in the graph: ");
    scanf("%d", &n);

    int** cost = (int**)calloc(n,sizeof(int*));
    printf("Enter the cost matrix:\n");
    for (i = 0; i < n; i++) {
        int* rowcost = (int*)calloc(n,sizeof(int));
        for (j = 0; j < n; j++) {
            scanf("%d", &rowcost[j]);
        }
        cost[i] = rowcost;
    }

    prim(n, cost);

    return 0;
}