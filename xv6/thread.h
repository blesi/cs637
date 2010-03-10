#include "user.h"
#include "param.h"
    
int thread_create(void *(*start_routine)(void*), void *arg);
static inline uint xchg(volatile uint *addr, uint newval);

// Lock Structures
typedef struct mutex_t {
    volatile uint locked;
} mutex_t;

// Condition Var Struct
typedef struct cond_t {
    char cond;
} cond_t;

int thread_wait(void);

int 
thread_create(void *(*start_routine)(void*), void *arg) 
{

  void *stack;
  int mpid;
  // Check stack.
  if((stack = malloc(1024)) == 0){
    return 0;
  }

  if ((mpid = tfork(stack, start_routine, arg)) < 0) {

      printf(1, "Error creating thread.\n");
      return -1;

  }

  return mpid;
}


// Mutual exclusion spin locks.

void
mutex_lock(mutex_t *m)
{

  while(xchg(&(m->locked), 1) == 1)
    ;

}


// Release the lock.
void
mutex_unlock(mutex_t *m)
{

  xchg(&(m->locked), 0);

}

void 
cond_wait(cond_t *c, mutex_t *m)
{

    // mutex_unlock(m);

    // condwait(c, m);

    // mutex_lock(m);

}

cond_signal(cond_t *c) 
{

    // condsig(c);

}

static inline uint
xchg(volatile uint *addr, uint newval)
{
  uint result;
  
  // The + in "+m" denotes a read-modify-write operand.
  asm volatile("lock; xchgl %0, %1" :
               "+m" (*addr), "=a" (result) :
               "1" (newval) :
               "cc");
  return result;
}
