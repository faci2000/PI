#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct node
{
    int val;
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

void push_back(struct connections* vert,int next_vert)
{
    struct node* temp=(struct node*)malloc(sizeof(struct node));
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

bool path_exist(struct connections* Graph,int* start, int* dest,int* size)
{
    bool* Visited=(bool*)calloc(*size,sizeof(bool));
    Visited[*start]=true;
    bool temp =find_path_dfs(Graph,Visited,*start, dest);
    free(Visited);
    return temp;   
}



int main()
{
    int vertices,edges,questions;scanf("%d %d %d",&vertices,&edges,&questions);
    struct connections* Graph=(struct connections*)malloc(vertices*sizeof(struct connections));
    for( int i=0;i<vertices;i++)
        connections_init(&Graph[i]);
    for(int i=0;i<edges;i++)
    {
        int temp_1,temp_2;scanf("%d %d",&temp_1,&temp_2);
        push_back(&Graph[temp_1],temp_2);
        push_back(&Graph[temp_2],temp_1);
    }
    for(int i=0;i<questions;i++)
    {
        int temp_1,temp_2;scanf("%d %d",&temp_1,&temp_2);
        printf(path_exist(Graph,&temp_1,&temp_2,&vertices)?"YES\n":"NO\n");
    }
    for( int i=0;i<vertices;i++)
        free_connections(&Graph[i]);
    free(Graph);
}