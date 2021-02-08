#include <stdlib.h>
#include <stdio.h>

struct PCB{
    int at,at2,bt,tat,wt;
}p[10];

int main(){
    int i,j,k,n;
    int ct[100],seq[100];
    int min,max,start,pos,idle=0;
    float avg_tat=0,avg_wt=0;

    //Entering the Input
    printf("Enter the number of process:\n ");
    scanf("%d",&n);
    printf("*******Input********\n");
    printf("Enter the Arrival time:\n");
    for(i=0;i<n;i++){
        scanf("%d",&p[i].at);
        p[i].at2 = p[i].at;
    }

    printf("Enter the Burst Time:\n");
    for(i=0;i<n;i++){
        scanf("%d",&p[i].bt);
    }

    //making 'start' the least arrival time
    start = p[0].at;
    for(i=1;i<n;i++){
        if(start>p[i].at){
            start=p[i].at;
        }
    }

    //making 'max' larger than the largest arrival time
    for(i=0;i<n;i++){
        if(max<p[i].at){
            max=p[i].at;
        }
    }
    max=max+1;

    printf("********Output*******\n");
    printf("Sequence of execution:\n");

    for(i=0;i<n;i++,k++){
        min=max;
        //getting the least arrival time index and value
        for(j=0;j<n;j++){
            if(p[j].at!=-1){  //to check weather the arrival time is used already
                if(p[j].at<min){
                    min=p[j].at;
                    pos=j;
                }
            }
        }
        seq[k] = pos;
        printf("[P%d]\t",pos);

        if(start<p[pos].at){  //if completion time is less than arrival time
            idle += p[pos].at - start;
            start = p[pos].at;
            start += p[pos].bt;
            ct[pos] = start;
            p[pos].at = -1;
        }
        else{   //completion time is greater than arrival time
            start+=p[pos].bt;
            ct[pos] = start;
            p[pos].at = -1;
        }
    }
    printf("\n");
    for(i=0;i<n;i++){
        p[i].tat = ct[i] - p[i].at2;
        p[i].wt = p[i].tat - p[i].bt;
    }
    printf("Process     Arrival Time(s)     Burst Time(s)       Turn Around Time(s)     Waiting Time(s)\n");
    for(i=0;i<n;i++)
    {
      printf("P%d            %d                 %d                     %d                      %d\n",i,p[i].at2,p[i].bt,p[i].tat,p[i].wt);
    }
    for(i=0;i<n;i++){
        avg_wt += (float) p[i].wt;
        avg_tat += (float) p[i].tat;
    }
    avg_tat = avg_tat/n;
    avg_wt = avg_wt/n;
    printf("Average Turn Around Time(s): %.2f\n",avg_tat);
    printf("Average Waiting Time(s): %.2f\n",avg_wt);
    printf("CPU Idle Time(s): %d\n",idle);
}
