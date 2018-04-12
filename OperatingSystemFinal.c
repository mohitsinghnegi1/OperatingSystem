#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>
#include<semaphore.h>
#define MAX_RESOURCES 7
sem_t mutex;
sem_t mutex1;
int available_Licences=MAX_RESOURCES;
/*decrease available resources by count resources*/



void *decrease_count(void *coun)
{	int *count =coun;
    
	

		sem_wait(&mutex);
		while(available_Licences<*count)
		printf("\n>>>>>>> Client is Waiting to get %d Licences Because Available Resource is %d <<<<<<<",*count,available_Licences);
		
		available_Licences-=*count;
		
		printf("\n:::::: Number of Licence Given to new Client is %d now Remaining Licences are %d :::::: \n ",*count,available_Licences);
		sem_post(&mutex);
		
		
		increase_count(*count);
		
	
}
/*when a process want to return a number of resources ,it calls the increase count() function:
increase available _resources by count */
int increase_count(int coun)
{     	sem_wait(&mutex1);  
		int count =coun;
		available_Licences+=count;
		
		printf("\n:::::: Number of Licence Expired are %d now Availability Of Resources Increased to %d ::::::\n",count,available_Licences);
		sem_post(&mutex1);
		
}
int main()
{   
	printf("        **************************************************");
	printf("\n**************WELCOME TO LICENCE PROVIDER LTD*********************\n");
	printf("        **************************************************\n\n");
	getch();
	sem_init(&mutex,0,1);
	sem_init(&mutex1,0,1);
	pthread_t client[100];
	int count[100];
	int clients,i;
	
	printf("\n Enter the no of Clients :");
	scanf("%d",&clients);
	
	for(i=0;i<clients;i++)
	{
		printf("\n Enter no of Licence Client %d wants :",i+1);
		scanf("%d",&count[i]);
		if(count[i]>available_Licences)
		{
		printf("\n:::::: Requested Licence Exceed the availability of no of Licences plse Reducde the no of Licence ::::::\n");
		i=i-1;
	}
	}
	for(i=0;i<clients;i++)
	{
		pthread_create(&client[i],NULL,decrease_count,&count[i]);
	}
	for( i=0;i<clients;i++)
	{
		pthread_join(client[i],NULL);
	}


}
