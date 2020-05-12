#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define infinity __INT32_MAX__

struct node
{
    int val;
    int dist;
    struct node* next;
};

struct connections
{
    struct node* first;
};

void connections_init(struct connections* vert)
{
    struct node* temp=(struct node*)malloc(sizeof(struct node));
    temp->val=-1;
    temp->next=NULL;
    vert->first=temp;
}

void push_back(struct connections* vert,int next_vert, int dist)
{
    struct node* temp=(struct node*)malloc(sizeof(struct node));
    temp->dist=dist;
    temp->val=next_vert;
    temp->next=vert->first;
    vert->first=temp;
}

void free_connections(struct connections* vert)
{
    struct node* temp=vert->first->next;
    while(vert->first!=NULL)
    {
        free(vert->first);
        vert->first=temp;
        if(temp!=NULL)
            temp=temp->next;
    }
}

bool Bellman_Ford(struct connections *Graph,int *vertices,int *start,int *end,int *Cost)
{
    bool change=true;
    int loop=0;
    Cost[*start]=0;
    while(change)
    {
        if(loop>*vertices-1)
            return false;
        loop++;
        change=false;
        for(int i=0;i<*vertices;i++)
        {
            struct node* temp = Graph[i].first;
            while(temp->next!=NULL)
            {
                if(Cost[temp->val]>(long long)Cost[i]+temp->dist)
                {
                    Cost[temp->val]=(long long)Cost[i]+temp->dist;
                    change=true;
                }
                temp=temp->next;
            }
        }
    } 
    return true;
}

bool find_path_dfs(struct connections* Graph,bool* Visited,int x, int* dest)
{
    if(x==*dest)
        return true;
    struct node* temp=Graph[x].first;
    while (temp->next!=NULL)
    {
        if(!Visited[temp->val])
        {
            Visited[temp->val]=true;
            if(find_path_dfs(Graph,Visited,temp->val,dest))
                return true;
        }
        temp=temp->next;
    }
    return false;
    

}

bool reachable(struct connections* Graph,int* start, int* dest,int* size)
{
    bool* Visited=(bool*)calloc(*size,sizeof(bool));
    Visited[*start]=true;
    bool temp =find_path_dfs(Graph,Visited,*start, dest);
    free(Visited);
    return temp;   
}
int main()
{
    int vertices,edges; scanf("%d %d",&vertices,&edges);
    int start,end;scanf("%d %d",&start,&end);
    struct connections* Graph=(struct connections*)malloc(vertices*sizeof(struct connections));
    for( int i=0;i<vertices;i++)
        connections_init(&Graph[i]);
    for(int i=0;i<edges;i++)
    {
        int temp_1,temp_2,temp_dist;scanf("%d %d %d",&temp_1,&temp_2,&temp_dist);
        push_back(&Graph[temp_1],temp_2,temp_dist);
    }
    int* Cost=(int*)calloc(vertices,sizeof(int));
    for(int i=0;i<vertices;i++)
        Cost[i]=infinity;
    if(!Bellman_Ford(Graph,&vertices,&start,&end,Cost))
    {
        printf("CYCLE\n");
    }
    else if(!reachable(Graph,&start,&end,&vertices))
    {
        printf("NO\n");
    } 
    else
    {
        printf("%d\n",Cost[end]);
    }
        
    free_connections(Graph);
    free(Graph);
}