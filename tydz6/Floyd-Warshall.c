#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#define infinity __INT32_MAX__


void Floyd_Warshall(int stations,int** Distance)
{
    
    for(int k=0;k<stations;k++)  
    {
        for(int i=0;i<stations;i++)
        {
            for(int j=0;j<stations;j++)
            {
                if((long long)Distance[i][j]>((long long)Distance[i][k]+Distance[k][j]))
                {
                    Distance[i][j]=(Distance[i][k]+Distance[k][j]);
                    //Distance[j][i]=(Distance[i][k]+Distance[k][j]);
                }
            }
        }
    }
    
}

int main()
{
    int lines, stations,questions;scanf("%d %d %d", &stations,&lines,&questions);
    int **Distance = (int**)malloc(stations*sizeof(int*));
    
    for(int i=0;i<stations;i++)
    {
        Distance[i]=calloc(stations,sizeof(int));
    }

    for(int i=0;i<stations;i++)
    {
        for(int j=0;j<stations;j++)
        {
            if(i==j)
                Distance[i][j]=0;
            else
                Distance[i][j]=infinity;
        }
    }

    for( int i=0;i<lines;i++)
    {
        int line_stations;scanf("%d",&line_stations);
        int start; scanf("%d",&start);
        for(int i=0;i<line_stations-1;i++)
        {
            int end,time;scanf("%d %d",&time,&end);
            if(Distance[start][end]>time)
            {
                Distance[start][end]=time;
                Distance[end][start]=time;
            }
            start=end;
        }
    }
    Floyd_Warshall(stations,Distance);
    //Distance[j][i]=Distance[i][j];
    // for(int i=0;i<stations;i++)
    // {
    //     for(int j=0;j<stations;j++)
    //         printf("%d ",Distance[i][j]);
    //     printf("\n");
    // }
    for(int i=0;i<questions;i++)
    {
        int start,end;scanf("%d %d",&start,&end);
        printf("%d\n", Distance[start][end]);
    }

    for(int i=0;i<stations;i++)
    {
        free(Distance[i]);
    }
    free(Distance);
}