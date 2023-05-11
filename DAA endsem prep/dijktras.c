#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
//dijktras -> shortest overall path tree
void dijktras(int n, int ** cost) {
  int * parent = (int * ) calloc(n, sizeof(int)); // keeps track of parent
  int * visited = (int * ) calloc(n, sizeof(int)); //keeps track of already visited
  long long * value = (long long * ) calloc(n, sizeof(long long)); //keeps track of min cost to reach particular node
  for (int i = 0; i < n; i++) {
    parent[i] = -1;
    visited[i] = 0; //0 = false 1 = true
    value[i] = LONG_MAX; //effectively initial cost to reach anything is infinite
  }
  visited[0] = 1;
  value[0] = 0; // since we will always start from first node in the list (can be changed)
  int current = 0; //index of current vertice
  int nodesreached = 1;
  while (nodesreached < n) {
    for (int j = 0; j < n; j++) {
      if (visited[j] != 1 && cost[current][j] != 0 && (value[current] + cost[current][j] < value[j])) {
        printf("%d %d\n", value[current], cost[current][j]);
        value[j] = value[current] + cost[current][j];
        parent[j] = current;
      }
      printf("%d for %d\n", value[1], parent[1]);
    }
    long min = LONG_MAX;
    for (int j = 0; j < n; j++) {
      if (visited[j] != 1 && value[j] < min) {
        current = j;
        min = value[j];
      }
    }
    visited[current] = 1;
    nodesreached++;
  }
  for (int i = 1; i < n; i++) {
    printf("%d - %d\n", parent[i], i);
  }
  for (int i = 0; i < n; i++) {
    printf("cost for reaching vertex %d : %d\n", i, value[i]);
  }
  free(parent);
  free(visited);
  free(value);
}

int main() {
  int n;
  printf("Enter size of the graph : ");
  scanf("%d", & n);
  int ** cost = (int ** ) calloc(n, sizeof(int * ));
  if (cost == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }
  for (int i = 0; i < n; i++) {
    int * rowcost = (int * ) calloc(n, sizeof(int));
    if (rowcost == NULL) {
      printf("Memory allocation failed\n");
      exit(1);
    }
    for (int j = 0; j < n; j++) {
      scanf("%d", & rowcost[j]);
      if (rowcost[j] == 0) { // Handle unreachable vertices
        rowcost[j] = INT_MAX;
      }
    }
    cost[i] = rowcost;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d\t", cost[i][j]);
    }
    printf("\n");
  }

  dijktras(n, cost);
  return 0;
}