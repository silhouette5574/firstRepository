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

void initialize(int **graph, int src, int dist[], int par[], int sptSet[], int v, int soln[]){
	int i;
	for(i = 0; i < v; i++){
		dist[i] = INT_MAX;
		par[0] = -1;
		sptSet[i] = 0;
		soln[i] = -1;
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

int printPath(int par[], int j, int soln[], int x){
	if(par[j] == -1){
		return x;
	}
	soln[x] = j;
	x++;
	printPath(par, par[j], soln, x);
	printf("%d ", j);
	}

int printSolution(int **graph, int dist[], int par[], int v, int src, int dest, int soln[]){
	int i, x = 0;
	printf("\nVertex\t\tDistance\t\tPath");
	//for(i = 1; i < v; i++){
        i = dest;
        printf("\n%d -> %d\t\t%d\t\t%d ", src, i, dist[i], src);
        x = printPath(par, i, soln, x);
        soln[x] = src;
	//}
}

int dijkstra(int **graph, int src, int dest, int v, int soln[]){
	int dist[v], sptSet[v], par[v], i, j;

	initialize(graph, src, dist, par, sptSet, v, soln);

	for(i = 0; i < v-1; i++){
		//i = dest;
		int u = minDistance(dist, sptSet, v);
		sptSet[u] = 1;
		for(j = 0; j < v; j++){
			relax(u, j, graph, par, dist, sptSet, v);
        }
	}
	printSolution(graph, dist, par, v, src, dest, soln);
	printf("\n");
	/*for(j = 0; j < v; j++){
		printf("%d ", soln[j]);
    }
	printf("\n");*/
	
	int temp[v];
	for(j = 0; j < v; j++){
		temp[j] = soln[j];
    }
    int x = 0;
    for(j = v-1; j >= 0; j--){
		if(soln[j] != -1){
			soln[j] = temp[x];
			x++;
		}
    }
    /*for(j = 0; j < v; j++){
		printf("%d ", soln[j]);
    }
	printf("\n");*/
	return dist[dest];
}

void findMin(int sp[], int *min, int *min_index, int size){
	int i;
	for(i = 0; i < size; i++){
		if (sp[i] < *min)
		{
			*min = sp[i];
			*min_index = i;
		}
	}
}

void secondShortest(int **graph, int src, int dest, int soln[], int v){
	int sp[v-1], i, j, temp, solution[v], d;
	int arr[v-1][v];
	for(j = 0; j < v-1; j++){
		sp[j] = INT_MAX;
    }
    int x = 0;
	for(j = 0; j < v; j++){
		solution[j] = soln[j];
    }
	for(i = 0; i < v-1; i++){
		if(solution[i] == -1 || solution[i+1] == -1)
			break;
		temp = graph[solution[i]][solution[i+1]];
		graph[solution[i]][solution[i+1]] = 0;
		d = dijkstra(graph, src, dest, v, soln);
		sp[i] = d;
		for(j = 0; j < v; j++){
			arr[i][j] = soln[j];
		}
		graph[solution[i]][solution[i+1]] = temp;
	}

	int min = INT_MAX, min_index = 0;
	findMin(sp, &min, &min_index, v-1);
	printf("\nSecond Shortest");
	printf("\n%d -> %d\t\t%d\t\t", src, dest, min);
	for(j = 0; j < v; j++){
		if(arr[min_index][j] == -1)
			break;
		printf("%d ", arr[min_index][j]);
    }
    printf("\n");
}

int main(){
    int v, i, j, src, dest;
    printf("Enter Number Of Vertices\n");
    scanf("%d", &v);
    int soln[v];
    int **graph = (int **)malloc(v * sizeof(int *));
    for(i = 0; i < v; i++){
         graph[i] = (int *)malloc(v * sizeof(int));
    }
    for(i = 0; i < v; i++){
        for(j = 0; j < v; j++){
            graph[i][j] = 0;
        }
    }

    scanf("%d%d", &src, &dest);

    createGraph(graph, v);
    dijkstra(graph, src, dest, v, soln);
    
    secondShortest(graph, src, dest, soln, v);    
    return 0;
}