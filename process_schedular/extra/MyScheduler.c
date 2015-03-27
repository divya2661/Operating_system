#include<stdio.h>
#include<signal.h>
#include<semaphore.h>
void FCFS(int p[],int ti[],int a[],int n)
{
	int i=0,status=0;
	for(i=0;i<n;i++)
	{
		kill(a[i],SIGCONT);
		wait(a[i],&status);
	}
}
void SJF(int p[],int ti[],int a[],int n)
{
	int i,j,status=0;
	for(i=0;i<n-1;i++)
	{
		for(j=i;j<n;j++)
		{
			if(ti[i]>ti[j])
			{
				int c=ti[i];
				ti[i]=ti[j];
				ti[j]=c;
				c=a[i];
				a[i]=a[j];
				a[j]=c;
			}
		}
	}
	for(i=0;i<n;i++)
	printf("%d\n",ti[i]);
	for(i=0;i<n;i++)
	{
		kill(a[i],SIGCONT);
		wait(a[i],&status);
	}

}
void priority(int p[],int ti[],int a[],int n)
{
	int i,j,status=0;
	for(i=0;i<n-1;i++)
	{
		for(j=i;j<n;j++)
		{
			if(p[i]>p[j])
			{int c=p[i];
			p[i]=p[j];
			p[j]=c;
			c=a[i];
			a[i]=a[j];
			a[j]=c;
			c=ti[i];
			ti[i]=ti[j];
			ti[j]=c;}
		}
	}
	for(i=0;i<n;i++)
	{
		kill(a[i],SIGCONT);
		wait(a[i],&status);
	}
}
void RR(int p[],int ti[],int a[],int n)
{
	
}
void queue(int p[],int ti[],int a[],int n)
{
}
void PSJF(int p[],int ti[],int a[],int n)
{
}
int main2(int p[],int ti[],int a[],int n)
{
	printf("Enter Scheduling option from menu\n1.FCFS\n2.SJF\n3.Priority\n4.Round Robin\n5.Multilevel feedback queue\n6.premptive SJF\n");
	int c,i;
	scanf("%d",&c);
	switch(c)
	{
		case 1:
		FCFS(p,ti,a,n);
		break;
		case 2:
		SJF(p,ti,a,n);
		break;
		case 3:
		priority(p,ti,a,n);
		break;
		case 4:
		RR(p,ti,a,n);
		break;
		case 5:
		queue(p,ti,a,n);
		case 6:
		PSJF(p,ti,a,n);
		break;
	}
	return 0;
}
