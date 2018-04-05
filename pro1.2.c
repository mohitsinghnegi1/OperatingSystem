#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>
#include<semaphore.h>
#define MAX_RESOURCES 5
sem_t mutex;
int available_resources=MAX_RESOURCES;
/*decrease available resources by count resources*/
/*return 0 if sufficient resources available*/
/*otherwise return -1*/
void *decrease_count(void *coun)
{		
int *count =coun;

	if(available_resources<*count)
	{	
		printf("\nNOT sufficient resources avaiable ,process need to wait for other process to free the resources");
		sem_wait(&mutex);
	
	}
	if ((available_resources>=*count))
	{
	
		available_resources-=*count;
		printf("resource value %d \n ",available_resources);
	
		sleep(2);
		
		increase_count(*count);
		
	}
}
/*when a process want to return a number of resources ,it calls the increase count() function:
increase available _resources by count */
int increase_count(int coun)
{
		int count =coun;
		available_resources+=count;
		printf("\nresouce aftr being free %d\n",available_resources);
		sem_post(&mutex);
		
}
int main()
{
	sem_init(&mutex,0,5);
	pthread_t t1,t2,t3,t4,t5;
	int count[5]={2,2,2,4,5};
	pthread_create(&t1,NULL,decrease_count,&count[0]);
	pthread_create(&t2,NULL,decrease_count,&count[1]);
	pthread_create(&t3,NULL,decrease_count,&count[2]);
	pthread_create(&t4,NULL,decrease_count,&count[3]);
	pthread_create(&t5,NULL,decrease_count,&count[4]);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
	pthread_join(t4,NULL);
	pthread_join(t5,NULL);
}
