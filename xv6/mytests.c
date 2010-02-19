#include "types.h"
#include "user.h"
#include "printf.h"
#include "thread.h"


#define ITERATIONS 1000
void increment(int *); 



int 
main() 
{

    int test = 4;

    int numThreads = 3;
    int fnshdtt;
    volatile int *x = malloc(sizeof(int));
    int i = 1;
    

    int numProcs = 3;
    int currentrunT;


    switch(test) {

    case 3:

        
    while (i <= numProcs) { 
        
        int currentrunT = 0;
        int myprocid = fork();

        if (myprocid == 0) {
            // spinloop
            
            // Set proportional ticket count 
            settn(i*100);

            for(currentrunT = 0; currentrunT < 100000; currentrunT++) {
              if (gettic() % 100 == 0) { 
              // printf(1,"Time: %d, TicketNum %d, RunCnt: %d\n", gettic(), settn(0), currentrunT);
              printf(1, "%d, %d, %d\n", gettic(), settn(0), currentrunT);
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

      numThreads = 1;

    //int mythreadid = thread_create(&increment, x);
    while (i <= numThreads) { 
        
        int mythreadid = thread_create(&increment, x);
        
        printf(1, "Starting Thread: %d\n", mythreadid);
        // unsigned int j = rand();
        // unsigned int k = gettic();

   
        // printf(1,"Random Number: %d\n", j%100);
        // printf(1, "NumTicks: %d\n", k);
        i++;
        // sleep(5);
    }
    // sleep(500);

    while (i > 1) {
    fnshdtt = twait();
    printf(1, "%dth finished thread: %d\n", numThreads - i + 1, fnshdtt);
    i--;
    }
    
    printf(1, "Expected x: %d  Total for x: %d\n", numThreads * ITERATIONS, *x); 
    exit();


  }


}

void
increment(int *myX) 
{

    printf(1, "hi\n");
    
  int i;
  for(i = 0; i < ITERATIONS; i++) {
      *myX++;
  }
    

}
