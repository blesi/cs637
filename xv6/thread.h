#include "user.h"
#include "param.h"
    
int thread_create(void *(*start_routine)(void*), void *arg);


int 
thread_create(void *(*start_routine)(void*), void *arg) 
{

  void *stack = malloc(1024);

  // Allocate kernel stack.
  if((stack = malloc(1024)) == 0){
    return 0;
  }

  // Set up stack to be able to call routine.
  // *(stack + 1020) = (start_routine);
  // *(stack + 1016) = arg;

  memmove(stack + 1016, (start_routine), sizeof((start_routine)));
  memmove(stack + 1020, arg, sizeof(arg));

  int mpid = tfork(stack);

  if(mpid == 0) {
      
      // test
      printf(1, "hia");
      
      // Execute passed routine
      (*start_routine)(arg);
      exit();

  } else {

      // Return pid of new thread
      return mpid;

  }

}

