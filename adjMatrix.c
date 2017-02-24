#include <stdio.h>
#define MAX 100
#include <stdlib.h>

int adj[MAX][MAX];
int n;

void create_graph();
void display();
void insert_edge(int, int);
void del_edge(int, int);

int main(){
	int ch, origin, dest;
	create_graph();
	while(1){
		printf("1. Insert an edge\n");
		printf("2. Delete an edge\n");
		printf("3. Display\n");
		printf("4. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &ch);
		switch(ch){
			case 1:
				printf("Enter the edge to be inserted: ");
				scanf("%d%d", &origin, &dest);
				insert_edge(origin, dest);
				break;
			case 2:
				printf("Enter the edge to be deleted: ");
				scanf("%d%d", &origin, &dest);
				del_edge(origin, dest);
				break;
			case 3: 
				display();
				break;
			case 4: 
				exit(1);
			default:
				printf("Wrong Choice\n");
				break;
		}
	}
}

void create_graph(){
	int i, max_edges, origin, dest;
	printf("Enter number of vertices: ");
	scanf("%d", &n);
	max_edges = n * (n-1);  //directed graph
	for(i = 1; i <= max_edges; i++){
		printf("Enter edge %d (-1 -1) to quit\n", i);
		scanf("%d%d", &origin, &dest);
		if((origin == -1) && (dest == -1))
			break;
		if(origin >= n || dest >= n || origin < 0 || dest < 0){
			printf("Invalid edge\n");
			i--;
		}
		else
			adj[origin][dest] = 1;
	}
}

void display(){
	int i, j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++)
			printf("%4d", adj[i][j]);
		printf("\n");
	}

}

void insert_edge(int origin, int dest){
	if(origin < 0 || origin >= n){
		printf("Origin vertex does not exist\n");
		return;
	}
	if(dest < 0 || dest >= n){
		printf("Destination vertex does not exist\n");
		return;
	}
	adj[origin][dest] = 1;
}

void del_edge(int origin, int dest){
	if(origin < 0 || origin >= n){
		printf("Origin vertex does not exist\n");
		return;
	}
	if(dest < 0 || dest >= n){
		printf("Destination vertex does not exist\n");
		return;
	}
	adj[origin][dest] = 0;
}
