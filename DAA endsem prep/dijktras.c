#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

int min_distance(int dist[], int visited[], int n) {
    int min_index, min_distance = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[i] < min_distance) {
            min_distance = dist[i];
            min_index = i;
        }
    }

    return min_index;
}

void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int n, int start) {
    int dist[n], visited[n];
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    dist[start] = 0;
    for (int i = 0; i < n - 1; i++) {
        int u = min_distance(dist, visited, n);
        visited[u] = 1;
        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !visited[v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    printf("Vertex\tDistance from Start\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\n", i, dist[i]);
    }
}

int main() {
    int n, start;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    int graph[MAX_VERTICES][MAX_VERTICES];

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter the start vertex: ");
    scanf("%d", &start);

    dijkstra(graph, n, start);

    return 0;
}
