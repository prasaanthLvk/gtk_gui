#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 

static pthread_t tid[3]; 
int counter; 
pthread_mutex_t lock; 

int osal_thread_create(void *thandle, int stacksize, void *func, void *param)
{
   int                  ret;
   pthread_attr_t       attr;
   pthread_t            *threadp;

   threadp = thandle;
   pthread_attr_init(&attr);
   pthread_attr_setstacksize(&attr, stacksize);
   ret = pthread_create(threadp, &attr, func, param);
   if(ret < 0)
   {
      return 0;
   }
   return 1;
}

void* trythis(void* arg) 
{ 
	pthread_mutex_lock(&lock); 

	unsigned long i = 0; 
	counter += 1; 
	printf("\n Job %d has started\n", counter); 

	for (i = 0; i < (0xFFFFFFFF); i++); 

	printf("\n Job %d has finished\n", counter); 

	pthread_mutex_unlock(&lock); 

	return NULL; 
} 

int main(void) 
{ 
	int i = 0; 
	int error; 

	if (pthread_mutex_init(&lock, NULL) != 0) { 
		printf("\n mutex init has failed\n"); 
		return 1; 
	} 
	
	osal_thread_create(&tid[0], 10000, &trythis,NULL );
	osal_thread_create(&tid[1], 10000, &trythis,NULL );
	osal_thread_create(&tid[2], 10000, &trythis,NULL );

	pthread_join(tid[0], NULL); 
	pthread_join(tid[1], NULL); 
	pthread_join(tid[2], NULL); 
	pthread_mutex_destroy(&lock); 

	return 0; 
} 

