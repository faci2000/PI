#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

struct phone_call
{
    int time;
    char number[16];
};


struct Queue
{
    struct phone_call tab[100000];
    int front,end;
};

void init_queue(struct Queue *q,int max_size)
{
    //q->tab[max_size];
    q->front=q->end=0;
}

void insert(struct Queue *q,int time, char number[16])
{
    q->tab[q->end].time=time;
    //q->tab[q->end].number[16];
    strcpy(q->tab[q->end].number,number);
    q->tab[q->end].time=time;
    q->end+=1;
}

// void insert(struct Queue *q,int time, char number[16])
// {
//     int i=q->front,j=q->end;
//     while(i<j)
//     {
//         int middle=(i+j)/2;
//         if(time>=q->tab[middle].time)
//             j=middle;
//         else
//         {
//             i=middle+1;
//         }
//     }
//     for(i=q->end;i>=j;i--)
//     {
//         q->tab[i+1].time=q->tab[i].time;
//         strcpy(q->tab[i+1].number,q->tab[i].number);
//     }
//     q->tab[j].time=q->time;
//     strcpy(q->tab[i+1].number,q->tab[i].number);
// }

int front_time(struct Queue *q)
{
    return q->tab[q->front].time;
}

char* front_number(struct Queue *q)
{
    return q->tab[q->front].number;
}

void pop(struct Queue *q)
{
    //free(q->tab[q->front].number);
    q->front+=1;
}

bool empty(struct Queue *q)
{
    if(q->end==q->front)
        return true;
    return false;
}

struct phone_call maximum(struct Queue *q)
{
    struct phone_call maax;
    maax.time=-1;
    if(!empty(q))
    {
        for(int i=q->front;i<=q->end;i++)
        {
            if(q->tab[i].time>=maax.time)
            {
                maax.time=q->tab[i].time;
                strcpy(maax.number,q->tab[i].number);
            }
        }
        return maax;
    }
    else
    {
        maax.time=-1;
        for(int i=0;i<16;i++)
            maax.number[i]='/0';
        return maax;
    }
}

struct phone_call extract_max(struct Queue *q)
{
    struct phone_call maax;
    maax=maximum(q);
    if(maax.time=-1)
        return maax;
    bool found=false;
    for(int i=q->front;i<=q->end;i++)
    {
        if(q->tab[i].time==maax.time&&strcmp(q->tab[i].number,maax.number)==0)
            found=true;

        if(found)
        {
            q->tab[i].time=q->tab[i+1].time;
            strcpy(q->tab[i].number,q->tab[i+1].number);
        }
    }
    q->end=-1;
    return maax;
}

void increase_key(struct Queue *q, int key, int new_key)
{
    for(int i=q->front;i<=q->end;i++)
    {
        if(q->tab[i].time==key&&q->tab[i].time<new_key)
        {
            q->tab[i].time=new_key;
            return;
        }
    }
    return;
}


// void destroy(struct Queue *q)
// {
//     free(q->tab);
// };


void take_phone_calls(int *nb)
{
    struct  Queue Calls_queue;
    init_queue(&Calls_queue,*nb);
    
    for(int i=0;i<*nb;i++)
    {
        char request;scanf("%s",&request);
        if(request=='a')
        {
            int time;scanf("%d",&time);
            char number[16];//=(char*)calloc(16,sizeof(char));
            scanf("%s",number);
            insert(&Calls_queue,time,number);
            //free(number);
        }
        else
        {
            int time;scanf("%d",&time);
            printf("%s %d\n",front_number(&Calls_queue),time-front_time(&Calls_queue));
            pop(&Calls_queue);
        }
        struct phone_call x;
        x=maximum(&Calls_queue);
        int key;scanf("%d",&key);
        increase_key(&Calls_queue,key,40)
    }
    //destroy(&Calls_queue);
}

int main()
{
    int nb;scanf("%d",&nb);
    take_phone_calls(&nb);
}