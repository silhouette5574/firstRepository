#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void createGraph(int **graph, int v){
	int i, max_edges, origin, dest, wt;
	int n = v;
	max_edges = n * (n-1);  //directed graph
	for(i = 1; i <= max_edges; i++){
		printf("Enter edge %d (-1 -1 -1) to quit\n", i);
		scanf("%d%d%d", &origin, &dest, &wt);
		if((origin == -1) || (dest == -1) || (wt == -1))
			break;
		if(origin >= n || dest >= n || origin < 0 || dest < 0 || wt < 0){
			printf("Invalid edge\n");
			i--;
		}
		else
			graph[origin][dest] = wt;
	}
}

void initialize(int **graph, int src, int dist[], int par[], int sptSet[], int v){
	int i;
	for(i = 0; i < v; i++){
		dist[i] = INT_MAX;
		par[0] = -1;
		sptSet[i] = 0;
	}
	dist[src] = 0;
}

void relax(int u, int j, int **graph, int par[], int dist[], int sptSet[], int v){
	if ((sptSet[j] == 0) && (graph[u][j] != 0) && dist[j] > dist[u] + graph[u][j]){
        par[j]  = u;
        dist[j] = dist[u] + graph[u][j];
    }
}

int minDistance(int dist[], int sptSet[], int v){
	int min = INT_MAX, min_index, i;
	for(i = 0; i < v; i++){
		if(sptSet[i] == 0 && dist[i] <= min){
			min = dist[i];
			min_index = i;
		}
	}
	return min_index;
}

void printPath(int par[], int j){
	if(par[j] == -1){
		return;
	}
	printPath(par, par[j]);
	printf("%d ", j);
}

int printSolution(int **graph, int dist[], int par[], int v){
	int src = 0, i;
	printf("Vertex\t\tDistance\t\tPath");
	for(i = 1; i < v; i++){
        printf("\n%d -> %d\t\t%d\t\t%d ", src, i, dist[i], src);
        printPath(par, i);
	}
}

void dijkstra(int **graph, int src, int v){
	int dist[v], sptSet[v], par[v], i, j;

	initialize(graph, src, dist, par, sptSet, v);

	for(i = 0; i < v-1; i++){
		int u = minDistance(dist, sptSet, v);
		sptSet[u] = 1;
		for(j = 0; j < v; j++){
			relax(u, j, graph, par, dist, sptSet, v);
        }
	}
	printSolution(graph, dist, par, v);
}

int main(){
    int v, i, j;
    printf("Enter Number Of Vertices\n");
    scanf("%d", &v);
    int **graph = (int **)malloc(v * sizeof(int *));
    for(i = 0; i < v; i++){
         graph[i] = (int *)malloc(v * sizeof(int));
    }
    for(i = 0; i < v; i++){
        for(j = 0; j < v; j++){
            graph[i][j] = 0;
        }
    }
    createGraph(graph, v);
    dijkstra(graph, 0, v);
    return 0;
}
