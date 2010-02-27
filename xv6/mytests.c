#include "types.h"
#include "user.h"
#include "printf.h"
#include "thread.h"


#define ITERATIONS 100000000
void *increment(int *); 
mutex_t mylock;

volatile int x;

int 
main(int argc, char *argv[]) 
{

    int test = 4;

    int numThreads = 3;
    int fnshdtt;
    // volatile int *x = malloc(sizeof(int));
    x = 0;
    int i = 1;
    

    int numProcs = 3;
    int currentrunT;

    switch(test) {

    case 3:

    numProcs = 3;    
    while (i <= numProcs) { 
        
        int myprocid = fork();

        if (myprocid == 0) {
            // spinloop
            
            // Set proportional ticket count 
            settn(i*100);

            for(currentrunT = 0; currentrunT < 100000; currentrunT++) {
              if (gettic() % 50 == 0) { 
                  printf(1,"Time: %d, TicketNum %d, RunCnt: %d\n", gettic(), settn(0), currentrunT);
              }

            }
            exit();

        } else {
            // fnshdtt = wait();

        }

        i++;

      }

   
    while( i > 1) {    

        fnshdtt = wait();
        i--;
    }

    // printf(1, "expected x: %d  total for x: %d\n", numthreads * iterations, *x); 
      exit();
 
 
      break;
    case 4:

      numThreads = (int) *argv[1] - 48;
      if(numThreads < 0 || numThreads > 9) 
          exit();
      // printf(1, "NumThreads: %d\n", numThreads);

    //int mythreadid = thread_create(&increment, x);
    while (i <= numThreads) { 
        
        // printf(1, "Pre ThreadID X Addr: %p  X Val: %d\n", (void *) x, *x);


        int mythreadid = thread_create(&increment, &x);
        mutex_lock(&mylock);
        printf(1, "Starting Thread: %d\n", mythreadid);
        mutex_unlock(&mylock);
 
        i++;
        // sleep(5);
    }
    // sleep(500);

    while (i > 1 ) {
    fnshdtt = twait();
    mutex_lock(&mylock);
    printf(1, "%dth finished thread: %d\n", numThreads - i + 1, fnshdtt);
    mutex_unlock(&mylock);
    i--;
    }
    // increment(x);
    printf(1, "Expected x: %d  Total for x: %d\n", numThreads * ITERATIONS, x); 
    exit();


  }


}

void *
increment(int *myX) 
{

  // printf(1, "\n :) \n :) \n");
   
  int i;
  for(i = 0; i < ITERATIONS; i++) {
      // (*myX)++;
      
      x++;

/*
      if(i%500 == 0) { 
          // mutex_lock(&mylock);
          // printf(1, "Proc: %d Iter: %d\n", getpid(), i);
          // mutex_unlock(&mylock);
      }
*/     
  }
  exit();
    
}
