#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void max_spanning_tree(int n, int **cost) {
    int *visited = calloc(n, sizeof(int));
    int *parent = calloc(n, sizeof(int));
    int u, v, max, maxcost = 0;

    visited[0] = 1;
    for (int i = 1; i < n; i++) {
        max = INT_MIN;
        for (int j = 0; j < n; j++) {
            if (visited[j]) {
                for (int k = 0; k < n; k++) {
                    if (cost[j][k] == 0) continue;
                    if (cost[j][k] > max && !visited[k]) {
                        max = cost[j][k];
                        u = j;
                        v = k;
                    }
                }
            }
        }
        visited[v] = 1;
        parent[v] = u;
        maxcost += max;
    }
    printf("Edges in the maximum spanning tree:\n");
    for (int i = 0; i < n; i++) {
        if (parent[i] != -1) {
            printf("%d - %d\n", parent[i], i);
        }
    }
    printf("Maximum cost: %d\n", maxcost);

    free(visited);
    free(parent);
}

int main() {
    int n;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Invalid number of vertices\n");
        return 1;
    }
    int **cost = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        cost[i] = malloc(n * sizeof(int));
    }
    printf("Enter the cost matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] < 0) {
                printf("Invalid cost matrix\n");
                return 1;
            }
        }
    }
    max_spanning_tree(n, cost);
    return 0;
}
