#include "user.h"
#include "param.h"
    
int thread_create(void *(*start_routine)(void*), void *arg);


int 
thread_create(void *(*start_routine)(void*), void *arg) 
{

  char *stack = malloc(KSTACKSIZE);

  // Allocate kernel stack.
  if((stack = malloc(KSTACKSIZE)) == 0){
    return 0;
  }

  int mpid = tfork(stack);

  if(mpid == 0) {

      // Execute passed routine
      (*start_routine)(arg);
      exit();

  } else {

      // Return pid of new thread
      return mpid;

  }

}

