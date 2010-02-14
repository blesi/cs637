#include "types.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"

extern unsigned int fastrand(unsigned int s);

int
sys_fork(void)
{
  int pid;
  struct proc *np;

  if((np = copyproc(cp)) == 0)
    return -1;
  pid = np->pid;
  np->state = RUNNABLE;
  return pid;
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return cp->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  if((addr = growproc(n)) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n, ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(cp->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

int
sys_gettic(void)
{
  // Enter Special Code Here !
  int n, ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  release(&tickslock);

  return ticks0;

}

// Set the ticknum to n
// if n == 0, return numtics.
// return 0 on success
int
sys_settn(int n)
{

  if (n == 0) 
    return cp->tctcnt;
  cp->tctcnt = n;
  return 0;

}

extern int sys_write(int, const char *, int);

unsigned int
sys_rand(void)
{

    int k = fastrand(ticks);
    // sys_write(1, "Done with fr", 13);
    return k;

}