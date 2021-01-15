#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

char buff[1024];

sem_t mysem;
//***********************************************************
void handler_read(void* arg)
{
  char* var = (char*)arg;

  //sleep(1);
  printf(" Read Handler thread %s\n", var);
 
  sem_wait(&mysem);
 //sem_post(&mysem);
  printf("READING SHARED BUFFER: %s\n", buff);
 sem_post(&mysem);

  pthread_exit(0);

}
//***********************************************************

void handler_write(void* arg)
{
  char* var = (char*)arg;

  printf(" Write Handler thread %s\n", var);
  sem_wait(&mysem);
  sprintf(buff, "%s","WRITING INTO SHARED BUFFER: Hello World You can see we have moved all the specific details (filenames, compiler flags, etc) into the macros on the top, and what remains below in the rules themselves, is expressed only in terms of those macros. There's nothing wrong with using a Makefile that is simple (as in Makefile1.txt, it is a choice for you about how fancy to get. " );
  sem_post(&mysem);
  //sleep(1);
  pthread_exit(0);
}
//***********************************************************

int main()
{
	pthread_t tid1, tid2;
	char* msg1="Thread 1 msg";
	char* msg2="Thread 2 msg";
        
	sem_init(&mysem,0,1);// 0 for thread nonzero for process
	//1 => binary semaphore

	pthread_create(&tid2, NULL, (void*)&handler_write, (void*)msg2);
	pthread_create(&tid1, NULL, (void*)&handler_read, (void*)msg1);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	sem_destroy(&mysem);
	//pthread_exit(0);
	
	return 0;

}
//***********************************************************
