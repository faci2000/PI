#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct node
{
    int val;
    struct node* next;
    struct node* twin;
    bool excluded;

};

struct connections
{
    struct node* first;
    int size;
};

void connections_init(struct connections* vert)
{
    struct node* temp=(struct node*)malloc(sizeof(struct node));
    temp->val=-1;
    temp->next=NULL;
    vert->first=temp;
    vert->size=0;
}

void push_back(struct connections* vert,int next_vert)
{
    struct node* temp=(struct node*)malloc(sizeof(struct node));
    temp->val=next_vert;
    temp->next=vert->first;
    temp->excluded=false;
    vert->first=temp;
    vert->size++;
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

int euler_paths(struct connections* Graph, int* size)
{
    int odd_amount=0;
    for(int i=0;i<*size;i++)
    {
        if(Graph[i].size%2==1)
            odd_amount++;
    }
    if(odd_amount==0)
    {
        int i=0;
        while(Graph[i].size==0)
            i++;
        Graph[i].size--;
        return 1;
    }
        
    return odd_amount/2;
}

void new_line(int x,struct connections* Graph,int* counter)
{
    while (Graph[x].first!=NULL&&Graph[x].first->excluded)
    {
        struct node* temp = Graph[x].first;
        Graph[x].first=Graph[x].first->next;
        //Graph[x].size--;
        free(temp);
    }
    if(Graph[x].first->val!=-1)
    {
        struct node* temp = Graph[x].first->next;
        int y=Graph[x].first->val;
        Graph[x].first->twin->excluded=true;
        free(Graph[x].first);
        Graph[x].first=temp;
        Graph[x].size--;
        Graph[y].size--;
        (*counter)++;
        new_line(y,Graph,counter);
        printf("%d ",x+1);
        return;
    }
    printf("%d ",(*counter)+1);
    printf("%d ",x+1);
}

void determine_lines(struct connections* Graph, int* size)
{
    for(int i=0;i<*size;i++)
    {
        int counter=0;
        if(Graph[i].size%2==1)
        {
            counter=0;
            new_line(i,Graph,&counter);
            printf("\n");
        }
    }
}

int main()
{
    int oioioi;scanf("%d",&oioioi);
    while(oioioi--)
    {
        int vertices,edges; scanf("%d %d",&vertices,&edges);
        struct connections* Graph=(struct connections*)malloc(vertices*sizeof(struct connections));
        for( int i=0;i<vertices;i++)
            connections_init(&Graph[i]);
        for(int i=0;i<edges;i++)
        {
            int temp_1,temp_2;scanf("%d %d",&temp_1,&temp_2);
            push_back(&Graph[temp_1-1],temp_2-1);
            push_back(&Graph[temp_2-1],temp_1-1);
            Graph[temp_1-1].first->twin=Graph[temp_2-1].first;
            Graph[temp_2-1].first->twin=Graph[temp_1-1].first;
        }
        printf("%d\n",euler_paths(Graph,&vertices));
        determine_lines(Graph,&vertices);
        for( int i=0;i<vertices;i++)
            free_connections(&Graph[i]);
        free(Graph);
    }
}