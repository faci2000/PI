#include<cstdio>
#include<cstdlib>
#include<time.h>
#include<iostream>
#include<stack>

using namespace std;


#define show_time
//#define alternative

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

bool dfs(int x, struct connections* Graph, short* Color, struct node** vert_list)
{
    Color[x]=1;
    struct node* temp=Graph[x].first;
    while (temp->next!=NULL)
    {
        if(Color[temp->val]==1)
            return true;
        else if(Color[temp->val]==0)
        {
            if(dfs(temp->val,Graph,Color,vert_list))
                return true;
        }
        temp=temp->next;
    }
    Color[x]=2;
    struct node* temp_2=(struct node*)malloc(sizeof(struct node));
    temp_2->val=x;
    temp_2->next=*vert_list;
    *vert_list=temp_2;
    return false;
}

bool alternativedfs(int x, struct connections* Graph, short* Color, stack<int>& vert_stack)
{
    Color[x]=1;
    struct node* temp=Graph[x].first;
    while (temp->next!=NULL)
    {
        if(Color[temp->val]==1)
            return true;
        else if(Color[temp->val]==0)
        {
            if(alternativedfs(temp->val,Graph,Color,vert_stack))
                return true;
        }
        temp=temp->next;
    }
    Color[x]=2;
    vert_stack.push(x);
    return false;
}

#if defined alternative
bool cycle_exist(struct connections* Graph,int* size,   stack<int>& vert_list)
{
    short* Color = (short*)calloc((*size),sizeof(short));
    for(int i=0;i<*size;i++)
    {
        if(Color[i]==0)
        {
            if(alternativedfs(i,Graph,Color,vert_list))
            {
                free(Color);
                return true;
            }
        }
    }
    free(Color);
    return false;
}
#else
bool cycle_exist(struct connections* Graph,int* size,struct node** vert_list)
{
    short* Color = (short*)calloc((*size),sizeof(short));
    for(int i=0;i<*size;i++)
    {
        if(Color[i]==0)
        {
            if(dfs(i,Graph,Color,vert_list))
            {
                free(Color);
                return true;
            }
        }
    }
    free(Color);
    return false;
}
#endif

int main()
{
    int vertices,edges; scanf("%d %d",&vertices,&edges);
    struct connections* Graph=(struct connections*)malloc(vertices*sizeof(struct connections));
    for( int i=0;i<vertices;i++)
        connections_init(&Graph[i]);
    
    for(int i=0;i<edges;i++)
    {
        int temp_1,temp_2;scanf("%d %d",&temp_1,&temp_2);
        push_back(&Graph[temp_1],temp_2);
    }
    #if defined show_time
        int timer =clock();
    #endif
    #if defined alternative
        stack<int> vert_list;
        if(!cycle_exist(Graph,&vertices,vert_list))
        {
            printf("OK\n");
            while(!vert_list.empty())
            {
                printf("%d ",vert_list.top());
                vert_list.pop();
            }
        }
        else
            printf("CYCLE\n");
    #else
        struct node* vert_list=NULL;
        if(!cycle_exist(Graph,&vertices,&vert_list))
        {
            printf("OK\n");
            struct node* temp=vert_list;
            while(vert_list!=NULL)
            {
                printf("%d ",vert_list->val);
                vert_list=vert_list->next;
                free(temp);
                temp=vert_list;
            }
        }
        else
            printf("CYCLE\n");
    #endif
    #if defined show_time
        printf("time: %fs\n",(double)(clock()-timer)/CLOCKS_PER_SEC);
    #endif
    
}