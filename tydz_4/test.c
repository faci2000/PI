#include<stdlib.h>
#include<stdio.h>

int is_letter(int a)
{
    if(a>='a'&&a<'z')
        return 1;
    if(a>='A'&&a<'Z')
        return 1;
    return -1;
}
void what(int tab[],int size)
{
    int swap=0;
    do{
        swap=0;
        for(int i=0;i<size-1;i++){
            if(tab[i]>tab[i+1]){
                int a=tab[i];
                tab[i]=tab[i+1];
                tab[i+1]=a;
                swap=1;
            }
        }
        size--;
        printf("x");
    }while (swap);
}

int main(){

    // int tab[10]={12,3,7,6,2,2};
    // what(tab,10);
    // for(int i=0;i<10;i++)
    //     printf("%d",tab[i]);
    int x;
    for(x=0;x<10;x++)
    {
        if(x%2==0)
            continue;
        printf("%d",x);
    }
    x=0;
    while(x<10)
    {
        if(x%2==0)
        {
            continue;
        }
        printf("%d",x);
        x++;
    }
}