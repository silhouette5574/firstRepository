#include<stdio.h>
#include<stdlib.h>
 
#define MAX 100  

int n;    
int adj[MAX][MAX];
 
void DfsUtil(int state[], int v){    
    int i;
    state[v] = 1;                                                     
    printf("%d ",v);

    for(i = 0; i < n; i++){
        if(adj[v][i] == 1 && state[i] == 0) 
            DfsUtil(state, i);
    }
}

void DFS(){
    int i, v;
    int state[n];
    
    for(i = 0; i < n; i++){               
        state[i] = 0;
    }

    printf("Enter Start Vertex for DFS: \n");    
    scanf("%d", &v);
    
    DfsUtil(state, v);
    printf("\n");
}

void create_graph(){
    int count,max_edge,origin,destin;
 
    printf("Enter number of vertices : ");
    scanf("%d",&n);
    max_edge = n*(n-1);
 
    for(count=1; count<=max_edge; count++){
        printf("Enter edge %d( -1 -1 to quit ) : ",count);
        scanf("%d %d",&origin,&destin);
 
        if((origin == -1) && (destin == -1))
            break;
 
        if(origin>=n || destin>=n || origin<0 || destin<0){
            printf("Invalid edge!\n");
            count--;
        }
        else{
            adj[origin][destin] = 1;
        }
    }
}

int main(){
    create_graph();
    DFS();
    return 0;
}
