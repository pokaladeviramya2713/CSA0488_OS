#include<stdio.h>

int main() 
{
    int bt[20],p[20],wt[20],tat[20],n,i,j,total=0,totalT=0;
	printf("Enter number of process");
    scanf("%d",&n);
	printf("Enter Burst Time\n");
    for(i=0;i<n;i++)
	 {
        printf("p%d",i+1);
        scanf("%d",&bt[i]);
        p[i]=i+1;
    }
	for (i=0;i<n;i++) 
	{
        wt[i]=0;
        for (j=0;j<i;j++)
		 {
            wt[i]+=bt[j];
        }
        total+=wt[i];
    }
	printf("\nProcess\t Burst Time \tWaiting Time\tTurnaround Time");
    for (i=0;i<n;i++)
	 {
        tat[i]=bt[i]+wt[i];
        totalT+=tat[i];
        printf("\np%d\t\t %d\t\t %d\t\t\t%d",p[i],bt[i],wt[i],tat[i]);
    }
	float avg_wt=(float)total/n;
    float avg_tat=(float)totalT/n;
    printf("\n\nAverage Waiting Time=%f",avg_wt);
    printf("\nAverage Turnaround Time=%f",avg_tat);
}
