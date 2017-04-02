#include<stdio.h>
#include<stdlib.h>
 
#define MAX 100  

int n;    
int adj[MAX][MAX];

void BFS();
void create_graph();
 
int queue[MAX], front = -1,rear = -1;

void insert_queue(int vertex);
int delete_queue();
int isEmpty_queue();
 
int main(){
    create_graph();
    BFS();
    return 0;
}
 
void BFS(){
    int i, v;
    int state[n]; 

    for(i = 0; i < n; i++)                       // 1. make all states zero
        state[i] = 0;
    
    printf("Enter Start Vertex for BFS: \n");    // 2. accept start vertex for bfs
    scanf("%d", &v);
    
    state[v] = 1;                                // 3. make the start vertex state = 1
    insert_queue(v);                             // 4. insert it in queue
    
    while(!isEmpty_queue())                      // 5. while queue is not empty
    {
        v = delete_queue( );                     // 6. delete element and print it
        printf("%d ",v);    
        state[v] = 1;                            // 7. make it state = 1
        
        for(i = 0; i < n; i++)                   // 8. make all adjacent vertices'(whose state = 0) state = 1 and insert them into queue
        {
            if(adj[v][i] == 1 && state[i] == 0) 
            {
                insert_queue(i);
                state[i] = 1;
            }
        }
    }
    printf("\n");
}
 
void insert_queue(int vertex){
    if(rear == MAX-1)
        printf("Queue Overflow\n");
    else{
        if(front == -1) 
            front = 0;
        rear = rear+1;
        queue[rear] = vertex ;
    }
}
 
int isEmpty_queue(){
    if(front == -1 || front > rear)
        return 1;
    else
        return 0;
}
 
int delete_queue(){
    int delete_item;
    if(front == -1 || front > rear){
        printf("Queue Underflow\n");
        exit(1);
    }
    
    delete_item = queue[front];
    front = front+1;
    return delete_item;
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