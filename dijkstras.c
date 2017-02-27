# include <stdio.h>
# include <stdlib.h>
#include <limits.h>

void dijkstra(int **, int, int*, int, int);

int main()
{
	int **adj, *parent1; //*parent2,*parent3;
	int n, i, u = 0, v, w, s, t, temp;
	scanf("%d",&n);
	adj = (int **)calloc(n,sizeof(int *));
	for(i=0;i<n;i++)
	{
		adj[i] = (int *)calloc(n,sizeof(int));
	}
	parent1 = (int *)calloc(n,sizeof(int));
	//parent2 = (int *)calloc(n,sizeof(int));
	//parent3 = (int *)calloc(n,sizeof(int));

	while(1)
	{
		scanf("%d%d%d", &u, &v, &w);
		if(u == -1)
			break;
		adj[u][v] = w;
	}
	scanf("%d%d",&s,&t);

	dijkstra(adj, n, parent1,s, t);

	temp=t;
	printf("\nPath1 : %d",t);
	while(temp!=s)
	{
		printf(" -> %d", parent1[temp]);
		temp = parent1[temp];
	}
	printf("\n");
	/* temp=t;
	   printf("\n path2: %d",t);
	   while(temp!=s)
	   {
	   printf("->%d",parent2[temp]);
	   temp=parent2[temp];
	   }
	   temp=t;
	   printf("\n path3: %d",t);
	   while(temp!=s)
	   {
	   printf("->%d",parent3[temp]);
	   temp=parent3[temp];
	   }*/
	return 0;
}

int minDistance(int dist[], int sptSet[], int n)
{
	int min = INT_MAX, min_index, v;
	for (v = 0; v < n; v++)
		if (sptSet[v] == 0 && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

void dijkstra(int **adj, int n, int parent1[], int s, int t)
{
	int dist[n], count, sptSet[n], i;
	for (i = 0; i < n; i++)
		dist[i] = INT_MAX, sptSet[i] = 0, parent1[i] = -1;

	dist[s] = 0;
	int cc = 0;
	for (count = 0; count < n-1; count++)
	{
		int u = minDistance(dist, sptSet, n);
		sptSet[u] = 1;
		int v;
		for (v = 0; v < n; v++)
			if (sptSet[v]==0 && adj[u][v] && dist[u] != INT_MAX && dist[u]+adj[u][v] < dist[v]){
				parent1[v] = u;
				dist[v] = dist[u] + adj[u][v];
			}
	}
	//printf("Distance of target from source = %d\n", dist[t]);	
}
