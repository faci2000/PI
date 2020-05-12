#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>

struct pixel
{
    int color;
    int x,y;
};

struct queue
{
    struct pixel tab[100000];
    int front,end;
};

void push_back(struct queue *Queue,int x,int y, int *color)
{
    Queue->tab[Queue->end].x=x;
    Queue->tab[Queue->end].y=y;
    Queue->tab[Queue->end].color=*color;
    Queue->end+=1;
}

void init(struct queue *Queue)
{
    Queue->front=0;
    Queue->end=0;
}

bool empty(struct queue *Queue)
{
    if(Queue->front==Queue->end)
        return true;
    else
        return false;
    
}

struct pixel front(struct queue *Queue)
{
    return (Queue->tab[Queue->front]);
}

void pop(struct queue *Queue)
{
    Queue->front+=1;
}

void get_updates(int *updates,struct queue *Queue)
{
    init(Queue);
    for(int i=0;i<*updates;i++)
    {
       int x,y,color;scanf("%d %d %d",&x,&y,&color);
       push_back(Queue,x,y,&color);
    }
}

void update(int **Color,int *tab_size,int *updates)
{
    struct queue Queue;
    get_updates(updates,&Queue);
    while(!empty(&Queue))
    {
        struct pixel temp=front(&Queue);
        if(Color[temp.x][temp.y]==0)
        {
            Color[temp.x][temp.y]=temp.color;
            if(temp.x+1<*tab_size&&Color[temp.x+1][temp.y]==0)
                push_back(&Queue,temp.x+1,temp.y,&temp.color);

            if(temp.x-1>=0&&Color[temp.x-1][temp.y]==0)
                push_back(&Queue,temp.x-1,temp.y,&temp.color);

            if(temp.y-1>=0&&Color[temp.x][temp.y-1]==0)
                push_back(&Queue,temp.x,temp.y-1,&temp.color);

            if(temp.y+1<*tab_size&&Color[temp.x][temp.y+1]==0)
                push_back(&Queue,temp.x,temp.y+1,&temp.color);    
        }
        pop(&Queue);
    }
    pop(&Queue);
}
 
int main()
{
    int tab_size,new_colors;scanf("%d %d",&tab_size,&new_colors);
    int **Color=(int**)malloc(tab_size*sizeof(int*));        
    for(int i=0;i<tab_size;i++)
    {
        Color[i]=(int*)malloc(tab_size*sizeof(int));
        for(int j=0;j<tab_size;j++)
        {
            scanf("%d",&Color[i][j]);
        }
    }
    update(Color,&tab_size,&new_colors);
    for(int i=0;i<tab_size;i++)
    {
        for(int j=0;j<tab_size;j++)
        {
            printf("%d ",Color[i][j]);
        }
        printf("\n");
        free(Color[i]);
    }
    free(Color);
    

}

