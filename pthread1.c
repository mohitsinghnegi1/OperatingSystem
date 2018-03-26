#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#include<sys/types.h>
#define MAX_RESOURCES 5

int available_resources=MAX_RESOURCES;
void decrement_count()
{
		printf("\ninitial value of resources %d",available_resources);
		available_resources-=1;
		printf("\nresource under use %d",available_resources);
		sleep(1);
		available_resources+=1;
		printf("\n resource aftr termination  %d",available_resources);
}
int main()
{
	int n;
	while(1)
	{
		while(1)
		{
			printf("\nget Licence\n\n");
			printf("\n Enter your choice");
			printf("\n1.get your licence\n2.Exit System");
			int ch;
			scanf("%d",&ch);
			if(ch==1)
			{
					if(available_resources>0)
					{
						pthread_t tid[10];
						int count;
						pthread_create(&tid[0],NULL,decrement_count,NULL);
							pthread_create(&tid[1],NULL,decrement_count,NULL);
						pthread_join(tid[0],NULL);
						pthread_join(tid[1],NULL);
					}
					else
					{
						printf("\n unavailabilty of resources plse try later""");
					}
			}
			else if(ch==2)
			{
				return(0);
			}
		}
	}
}
