#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>
#include<semaphore.h>
#define MAX_RESOURCES 7
sem_t mutex;
int available_resources=MAX_RESOURCES;
/*decrease available resources by count resources*/


void *decrease_count(void *coun)
{	int count =2;
    
	if(available_resources<count)
	{	
		printf("\nNOT sufficient resources avaiable ,process need to wait for other process to free the resources");
		sleep(2);
	
	}
	if(available_resources>=count)
	{
		sem_wait(&mutex);
		available_resources-=count;
		printf("resource value %d \n ",available_resources);
		sem_post(&mutex);
		sleep(2);
		sem_wait(&mutex);
		increase_count(count);
		
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
	sem_init(&mutex,0,1);
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
