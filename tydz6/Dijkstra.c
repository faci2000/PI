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

int Dijkstra(struct connections *Graph,int *vertices,int *start,int *end)
{
    bool *Set = (bool*)calloc(*vertices,sizeof(bool));
    int *Distance = (int*)malloc(*vertices*sizeof(int));
    for(int i=0;i<*vertices;i++)
        Distance[i]=infinity;
    Distance[*start]=0;
    for(int i=0;i<*vertices;i++)
    {
        int mini=infinity;
        for(int j=0;j<*vertices;j++)
        {
            if(mini==infinity)
            {
                if(!Set[j])
                    mini=j;
                continue;
            }    
            if(Distance[mini]>Distance[j]&&!Set[j])
                mini=j;
        }
        Set[mini]=true;
        while (Graph[mini].first->next!=NULL)
        {
            if(!Set[Graph[mini].first->val]&&Distance[Graph[mini].first->val]>((long long)Graph[mini].first->dist+Distance[mini]))
                Distance[Graph[mini].first->val]=Graph[mini].first->dist+Distance[mini];
            struct node* temp = Graph[mini].first;
            Graph[mini].first=Graph[mini].first->next;
            free(temp);
        }
    }
    int result = Distance[*end];
    free(Distance);
    free(Set);
    return result;
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
        push_back(&Graph[temp_2],temp_1,temp_dist);
    }
    
    printf("%d\n",Dijkstra(Graph,&vertices,&start,&end));
    free_connections(Graph);
    free(Graph);
}