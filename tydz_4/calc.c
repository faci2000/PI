#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Stack
{
    int *tab;
    int top;
};

void init_stack(struct Stack *s,int max_size)
{
    s->tab=(int*)malloc(max_size*sizeof(int));
    s->top=0;
}

void push(struct Stack *s,int value)
{
    s->tab[s->top]=value;
    s->top+=1;
}

bool empty(struct Stack *s)
{
    if(s->top==0)
        return true;
    else 
        return false;
}

int top(struct Stack *s)
{
    return s->tab[s->top-1];
}

void pop(struct Stack *s)
{
    s->top-=1;
}

void destroy(struct Stack *s)
{
    free(s->tab);
}

int pot(int a,int b)
{
    if (b==0)
        return 1;
    else
    {
        if (b%2==0)
        {
            int w=pot(a,b/2);
            return w*w;
        }
        else
        {
            int w=a*pot(a,b-1);
            return w;

        }
    }
}

int get_dec_val(char* number, int* length)
{
    int dec=1,i=0,dec_val=0;
    while ((int)number[i]!=0&&i<*length)
    {
        dec_val*=dec;
        dec*=10;
        dec_val+=(int)number[i]-(int)'0';
        i++;
    }
    return dec_val;
}

void perf_operation(char* sign,struct Stack* ONP_stack)
{
    if(*sign=='+')
    {
        int result=top(ONP_stack);
        pop(ONP_stack);
        result+=top(ONP_stack);
        pop(ONP_stack);
        push(ONP_stack,result);
    }
    else if(*sign=='-')
    {
        int result=top(ONP_stack);
        pop(ONP_stack);
        result=top(ONP_stack)-result;
        pop(ONP_stack);
        push(ONP_stack,result);
    }
    else if(*sign=='*')
    {
        int result=top(ONP_stack);
        pop(ONP_stack);
        result*=top(ONP_stack);
        pop(ONP_stack);
        push(ONP_stack,result);
    }
    else if(*sign=='/')
    {
        int result=top(ONP_stack);
        pop(ONP_stack);
        result=top(ONP_stack)/result;
        pop(ONP_stack);
        push(ONP_stack,result);
    }
    else if(*sign=='%')
    {
        int result=top(ONP_stack);
        pop(ONP_stack);
        result=top(ONP_stack)%result;
        pop(ONP_stack);
        push(ONP_stack,result);
    }
    else
    {
        int result=top(ONP_stack);
        pop(ONP_stack);
        result=pot(top(ONP_stack),result);
        pop(ONP_stack);
        push(ONP_stack,result);
    }
}

int calc_result(int i,int *nb_size)
{
    struct Stack ONP_stack;
    init_stack(&ONP_stack,(i+1)/2);
    while(i--)
    {
        char* elem = (char*)calloc(*nb_size,sizeof(char));
        scanf("%s",elem);
        if((int)elem[0]>=(int)'0'&&(int)elem[0]<=(int)'9')
        {
            push(&ONP_stack,get_dec_val(elem,nb_size));
        }
        else
        {
            perf_operation(&elem[0],&ONP_stack);
        }   
    }
    i=top(&ONP_stack);
    destroy(&ONP_stack);
    return i;
}

int main()
{
    int count,nb_size;scanf("%d %d",&count,&nb_size);
    printf("%d\n",calc_result((2*count-1),&nb_size));
}