#include "types.h"
#include "user.h"
#include "printf.h"
#include "thread.h"

#define ITERATIONS 100000
#define NUM_PROCS 3
#define NUM_THREADS 9

volatile int x = 0;
mutex_t lock;
mutex_t print_lock;

void processTest() {
  int i;
  for (i = 1; i <= NUM_PROCS; i++) {
        int currentrunT = 0;
        int myprocid = fork();
        if (myprocid == 0) {
          // spinloop

          // Set proportional ticket count             
	  settn(i*100);

	  for(currentrunT = 0; currentrunT < 100000; currentrunT++) {
	    if (gettic() % 50 == 0) { 
	      printf(1,"Time: %d, TicketNum %d, RunCnt: %d, PID:%d\n", gettic(), settn(0), currentrunT, getpid());
	    }
          }
          exit();
        } else if (myprocid < 0) {
	  printf(1, "Error launcing process %d!\n", i);
	  exit();
	}
  }
   
  while(i > 1) {
    int processId = wait();
    printf(1, "Process %d finished!\n", processId);
    i--;
  }
}

void threadTest(void *(*start_routine)(void*)) {
  int i;
  for (i = 0; i < NUM_THREADS; i++) { 
    int mythreadid = thread_create(start_routine, 0);
    mutex_lock(&print_lock);    
    printf(1, "Create: %d!\n", mythreadid);
    mutex_unlock(&print_lock);
  }
  
  while (i > 0) {
    int threadId = thread_wait();
    mutex_lock(&print_lock);
    printf(1, "Finished thread %d at %d!\n", threadId, x);
    mutex_unlock(&print_lock);
    i--;
  }
    
  printf(1, "Expected x: %d  Total for x: %d\n", NUM_THREADS * ITERATIONS, x);
}


void*
lock_increment(void* arg) 
{
  int* myX = (int*) arg;
  int i;
  mutex_lock(&print_lock);
  printf(1, "Begin: %d!\n", getpid());
  mutex_unlock(&print_lock);
  for(i = 0; i < ITERATIONS; i++) {
    mutex_lock(&lock);
    //printf(1, "%d t%d!\n", x, getpid());
    int xTemp = x;
    xTemp++;
    x=xTemp;
    mutex_unlock(&lock);
  }
  exit();
}

void*
race_increment(void* arg) 
{
  int* myX = (int*) arg;
  int i;
  printf(1, "Begin: %d!\n", getpid());
  for(i = 0; i < ITERATIONS; i++) {
    //printf(1, "%d t%d!\n", x, getpid());
    int xTemp = x;
    xTemp++;
    x=xTemp;
  }
  exit();
}

int main(int argc, char* argv[]) 
{
  int testNum = 1;
  if (argc == 2) {
    testNum = atoi(argv[1]);
  }

  switch (testNum) {
  case 1:
    processTest();
    break;
  case 2:
    threadTest(&race_increment);
    break;
  case 3:
    threadTest(&lock_increment);
    break;
  default:
    printf(1, "Invalid Argument.\nUsage: mytests <test_num>\n");
  }
  exit();
}
