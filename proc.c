#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"
#include "synch.h"

struct _ptable {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;

static struct proc *initproc;

int nextpid = 1;
int nexttid = 1;
extern void forkret(void);
extern void trapret(void);
static void wakeup1(void *chan);

void
pinit(void)
{
  initlock(&ptable.lock, "ptable");
}

//PAGEBREAK: 32
// Look in the process table for an UNUSED proc.
// If found, change state to EMBRYO and initialize
// state required to run in the kernel.
// Otherwise return 0.
static struct proc*
allocproc(void)
{
  struct proc *p;
  char *sp;

  acquire(&ptable.lock);

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->state == UNUSED){
      goto found;
    }

  release(&ptable.lock);
  return 0;

found:
  p->state = EMBRYO;
  p->pid = nextpid++;
  p->nice = 20;
  p->tid = nexttid++;
  p->isthread = 1;
  p->tcount = 0;
  p->tparent = p;

  release(&ptable.lock);

  // Allocate kernel stack.
  if((p->kstack = kalloc()) == 0){
    p->state = UNUSED;
    return 0;
  }
  sp = p->kstack + KSTACKSIZE;

  // Leave room for trap frame.
  sp -= sizeof *p->tf;
  p->tf = (struct trapframe*)sp;

  // Set up new context to start executing at forkret,
  // which returns to trapret.
  sp -= 4;
  *(uint*)sp = (uint)trapret;

  sp -= sizeof *p->context;
  p->context = (struct context*)sp;
  memset(p->context, 0, sizeof *p->context);
  p->context->eip = (uint)forkret;

  return p;
}

//PAGEBREAK: 32
// Set up first user process.
void
userinit(void)
{
  struct proc *p;
  extern char _binary_initcode_start[], _binary_initcode_size[];
  
  p = allocproc();
  initproc = p;
  if((p->pgdir = setupkvm()) == 0)
    panic("userinit: out of memory?");
  inituvm(p->pgdir, _binary_initcode_start, (int)_binary_initcode_size);
  p->sz = PGSIZE;
  memset(p->tf, 0, sizeof(*p->tf));
  p->tf->cs = (SEG_UCODE << 3) | DPL_USER;
  p->tf->ds = (SEG_UDATA << 3) | DPL_USER;
  p->tf->es = p->tf->ds;
  p->tf->ss = p->tf->ds;
  p->tf->eflags = FL_IF;
  p->tf->esp = PGSIZE;
  p->tf->eip = 0;  // beginning of initcode.S

  safestrcpy(p->name, "initcode", sizeof(p->name));
  p->cwd = namei("/");

  p->state = RUNNABLE;
}

// Grow current process's memory by n bytes.
// Return 0 on success, -1 on failure.
int
growproc(int n)
{
  uint sz;
  
  sz = proc->sz;
  if(n > 0){
    if((sz = allocuvm(proc->pgdir, sz, sz + n)) == 0)
      return -1;
  } else if(n < 0){
    if((sz = deallocuvm(proc->pgdir, sz, sz + n)) == 0)
      return -1;
  }
  proc->sz = sz;
  switchuvm(proc);
  return 0;
}

// Create a new process copying p as the parent.
// Sets up stack to return as if from system call.
// Caller must set state of returned proc to RUNNABLE.
int
fork(void)
{
  int i, pid;
  struct proc *np;

  // Allocate process.
  if((np = allocproc()) == 0)
    return -1;

  // Copy process state from p.
  if((np->pgdir = copyuvm(proc->pgdir, proc->sz)) == 0){
    kfree(np->kstack);
    np->kstack = 0;
    np->state = UNUSED;
    return -1;
  }
  np->sz = proc->sz;
  np->parent = proc;
  np->nice = proc->nice;
  np->tparent = np;////////////////////////
  *np->tf = *proc->tf;

  // Clear %eax so that fork returns 0 in the child.
  np->tf->eax = 0;

  for(i = 0; i < NOFILE; i++)
    if(proc->ofile[i])
      np->ofile[i] = filedup(proc->ofile[i]);
  np->cwd = idup(proc->cwd);

  safestrcpy(np->name, proc->name, sizeof(proc->name));
 
  pid = np->pid;

  // lock to force the compiler to emit the np->state write last.
  acquire(&ptable.lock);
  np->state = RUNNABLE;
  release(&ptable.lock);
  
  return pid;
}


void
exit(void)
{
  struct proc *p;
  int fd,i;

  if(proc == initproc)
    panic("init exiting");
  if(proc->isthread ==0){
    proc = proc->tparent;
  }
  // Close all open files.
  for(fd = 0; fd < NOFILE; fd++){
    if(proc->ofile[fd]){
      fileclose(proc->ofile[fd]);
      proc->ofile[fd] = 0;
    }
  }

  begin_op();
  iput(proc->cwd);
  end_op();
  proc->cwd = 0;
  acquire(&ptable.lock);

  // Parent might be sleeping in wait().
 wakeup1(proc->parent);

  // Pass abandoned children to init.
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    
    if(p->pid == proc->pid){
        p->state = ZOMBIE;
          wakeup1(p->parent);
    }
    if(p->parent == proc && p->isthread == 1){
        p->parent = initproc;
        if(p->state == ZOMBIE)
          wakeup1(initproc);

    }
  }
  for(i=0;i<7;i++){
    if(proc->tlist[i]!=0){
      proc->tlist[i]->state = ZOMBIE;
    }
  }
  // Jump into the scheduler, never to return.
  proc->state = ZOMBIE;
  sched();
  panic("zombie exit");
}

// Wait for a child process to exit and return its pid.
// Return -1 if this process has no children.
int
wait(void)
{
  struct proc *p;
  int havekids, pid,i;

  acquire(&ptable.lock);
  for(;;){
    // Scan through table looking for zombie children.
    havekids = 0;
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
      if(p->parent != proc)
        continue;
      havekids = 1;
      if(p->state == ZOMBIE){
        // Found one.
        pid = p->pid;
        kfree(p->kstack);
        p->kstack = 0;
        freevm(p->pgdir);
        p->state = UNUSED;
        p->pid = 0;
        p->parent = 0;
        p->name[0] = 0;
        p->killed = 0;
        p->tcount = 0;
        for(i=0;i<7;i++){
          if(p->tlist[i] != 0){
            p->tlist[i]->state = UNUSED;
            kfree(p->tlist[i]->kstack);
            p->tlist[i] = 0;
          }
        }
        release(&ptable.lock);
        return pid;
      }
    }

    // No point waiting if we don't have any children.
    if(havekids == 0 || proc->killed){
      release(&ptable.lock);
      return -1;
    }

    // Wait for children to exit.  (See wakeup1 call in proc_exit.)
    sleep(proc, &ptable.lock);  //DOC: wait-sleep
  }
}

int min_nice(void){
  int min = 41;
  struct proc * p;
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
        if(p->state == RUNNABLE && min > p->nice) 
          min = p->nice;
  }
  return min;
}
void
scheduler(void)
{
  struct proc *p;
  int min;
  for(;;){
    // Enable interrupts on this processor.
    sti();
    // Loop over process table looking for process to run.
    acquire(&ptable.lock);
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
      min = min_nice();
      if(p->nice == min && p->state == RUNNABLE){

        proc = p;
        switchuvm(p);
        p->state = RUNNING;
        swtch(&cpu->scheduler, proc->context);
        switchkvm();

        proc = 0;
      }
    }
    release(&ptable.lock);

  }
}

// Enter scheduler.  Must hold only ptable.lock
// and have changed proc->state.
void
sched(void)
{
  int intena;

  if(!holding(&ptable.lock))
    panic("sched ptable.lock");
  if(cpu->ncli != 1)
    panic("sched locks");
  if(proc->state == RUNNING)
    panic("sched running");
  if(readeflags()&FL_IF)
    panic("sched interruptible");
  intena = cpu->intena;
  swtch(&proc->context, cpu->scheduler);
  cpu->intena = intena;
}

// Give up the CPU for one scheduling round.
void
yield(void)
{
  acquire(&ptable.lock);  //DOC: yieldlock
  proc->state = RUNNABLE;
  sched();
  release(&ptable.lock);
}

// A fork child's very first scheduling by scheduler()
// will swtch here.  "Return" to user space.
void
forkret(void)
{
  static int first = 1;
  // Still holding ptable.lock from scheduler.
  release(&ptable.lock);

  if (first) {
    // Some initialization functions must be run in the context
    // of a regular process (e.g., they call sleep), and thus cannot 
    // be run from main().
    first = 0;
    iinit(ROOTDEV);
    initlog(ROOTDEV);
  }
  
  // Return to "caller", actually trapret (see allocproc).
}

// Atomically release lock and sleep on chan.
// Reacquires lock when awakened.
void
sleep(void *chan, struct spinlock *lk)
{
  if(proc == 0)
    panic("sleep");

  if(lk == 0)
    panic("sleep without lk");

  // Must acquire ptable.lock in order to
  // change p->state and then call sched.
  // Once we hold ptable.lock, we can be
  // guaranteed that we won't miss any wakeup
  // (wakeup runs with ptable.lock locked),
  // so it's okay to release lk.
  if(lk != &ptable.lock){  //DOC: sleeplock0
    acquire(&ptable.lock);  //DOC: sleeplock1
    release(lk);
  }

  // Go to sleep.
  proc->chan = chan;
  proc->state = SLEEPING;
  //cprintf("kungs\n");

  sched();

  // Tidy up.
  proc->chan = 0;

  // Reacquire original lock.
  if(lk != &ptable.lock){  //DOC: sleeplock2
    release(&ptable.lock);
    acquire(lk);
  }
}

//PAGEBREAK!
// Wake up all processes sleeping on chan.
// The ptable lock must be held.
static void
wakeup1(void *chan)
{
  struct proc *p;

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->state == SLEEPING && p->chan == chan)
      p->state = RUNNABLE;
}

// Wake up all processes sleeping on chan.
void
wakeup(void *chan)
{
  acquire(&ptable.lock);
  wakeup1(chan);
  release(&ptable.lock);
}

// Kill the process with the given pid.
// Process won't exit until it returns
// to user space (see trap in trap.c).
int
kill(int pid)
{
  struct proc *p;

  acquire(&ptable.lock);
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->pid == pid){
      p->killed = 1;
      // Wake process from sleep if necessary.
      if(p->state == SLEEPING)
        p->state = RUNNABLE;
      release(&ptable.lock);
      return 0;
    }
  }
  release(&ptable.lock);
  return -1;
}


//PAGEBREAK: 36
// Print a process listing to console.  For debugging.
// Runs when user types ^P on console.
// No lock to avoid wedging a stuck machine further.
void
procdump(void)
{
  static char *states[] = {
  [UNUSED]    "unused",
  [EMBRYO]    "embryo",
  [SLEEPING]  "sleep ",
  [RUNNABLE]  "runble",
  [RUNNING]   "run   ",
  [ZOMBIE]    "zombie"
  };
  int i;
  struct proc *p;
  char *state;
  uint pc[10];

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->state == UNUSED)
      continue;
    if(p->state >= 0 && p->state < NELEM(states) && states[p->state])
      state = states[p->state];
    else
      state = "???";
    cprintf("%d %s %s", p->pid, state, p->name);
    if(p->state == SLEEPING){
      getcallerpcs((uint*)p->context->ebp+2, pc);
      for(i=0; i<10 && pc[i] != 0; i++)
        cprintf(" %p", pc[i]);
    }
    cprintf("\n");
  }
}

int getpid(void){
  return proc->pid;
}

int thread_create(void *(*function)(void *), int priority, void *arg, void *stack){
  struct proc *p, *temp;
  char *sp;
  int i;
  
  acquire(&ptable.lock);

  for(p=ptable.proc;p<&ptable.proc[NPROC];p++)
    if(p->state == UNUSED)
      goto found;

  release(&ptable.lock);
  return -1;
  
found:
  temp = proc->tparent;

  p->state = EMBRYO;
  p->parent = temp;
  for(i=0;i<7;i++){
    if(temp->tlist[i]==0){
      temp->tlist[i] = p;
      break;
    }
  }
  if(i == 7){
    p->state = UNUSED;
    release(&ptable.lock);
    return -1;
  }
  p->isthread = 0;
  if(((p->kstack) = kalloc()) == 0){
    release(&ptable.lock);
    return -1;
  }
  p->nice = priority;
  p->pid = temp->pid;
  p->pgdir = temp->pgdir;
  p->cwd = temp->cwd;
  p->tid = nexttid++;
  p->sz = temp->sz;
  safestrcpy(p->name, proc->name, sizeof(proc->name));

  release(&ptable.lock);
  
  sp = p->kstack + KSTACKSIZE;

  sp -= sizeof *p->tf;
  p->tf = (struct trapframe*) sp;

  sp -= 4;
  *(uint*)sp = (uint)trapret;

  sp-= sizeof *p->context;
  p->context = (struct context*)sp;
  memset(p->context, 0, sizeof *p->context);
  p->context->eip = (uint)forkret;


  p->tparent = proc->tparent;////////////////////////
  *p->tf = *proc->tparent->tf;
  p->tf->eax = 0;


  for(i = 0; i < NOFILE; i++)
    if(proc->ofile[i])
      p->ofile[i] = filedup(proc->ofile[i]);
  p->cwd = idup(proc->cwd);

  safestrcpy(p->name, proc->name, sizeof(proc->name));

  p->tf->esp = (uint)stack;
  p->tf->esp += KSTACKSIZE -8;
  *(uint*)p->tf->esp = 0xFFFFFFFF;
  *(uint*)(p->tf->esp + 4) = (uint)arg;
  p->tf->ebp = p->tf->esp;
  p->tf->eip = (uint)function;



  acquire(&ptable.lock);

  p->state = RUNNABLE;

  release(&ptable.lock);
  yield();
  //cprintf("thread_create_out\n");
  return p->tid;
}


void thread_exit(void *retval){
  if(proc->isthread==1) { 
    exit();
  } else {
    acquire(&ptable.lock);
      wakeup1(proc);
    proc->state = ZOMBIE;
    proc->retval = retval;
    sched();
  }
}

int thread_join(int tid, void **retval){
  struct proc *maint;
  struct proc *ext;
  int i;
  acquire(&ptable.lock);
  maint = proc->tparent;
  while(1){
    if(tid==maint->tid){
      release(&ptable.lock);
      thread_exit(0);
    }
    for(i=0;i<7;i++){
      if(maint->tlist[i]->tid==tid){
        ext = maint->tlist[i];
        break;
      }
    }
    if(i==7){ 
      release(&ptable.lock);
      return -1;
    }
    if(ext->state==ZOMBIE){
      ext->state = UNUSED;
      maint->tlist[i] = 0;
      *retval = ext->retval;
      release(&ptable.lock);
      return 0;
    } 
    else 
      sleep(ext, &ptable.lock);
  }
  release(&ptable.lock);
  return -1;
}
int gettid(void){
  return proc->tid;
}






int mutex_init(struct mutex_t *mutex)
{
  if(mutex == 0)
    return -1;
  if(mutex->init == 1)
    return -2;
  if((mutex->flag=0) != 0)
    return -3;
  mutex->init=1;
  return 0;

}

int mutex_lock(struct mutex_t *mutex)
{
  if(mutex == 0)
    return -1;
  if(mutex->init != 1)
    return -2;
  if(proc->mtx)
    return -3;
  acquire(&ptable.lock);
  proc->mtx=mutex;
  if(!mutex->flag){
    mutex->flag=1;
  }
  else{
    while(1)
    {
      //cprintf("mtx->flag == 0\n");
      if(!proc->mtx->flag){
        //cprintf("kungs\n");
        break;
      }
      //procdump();
      sleep(proc,&ptable.lock);
    }
  }
  release(&ptable.lock);
  return 0;
}
int mutex_unlock(struct mutex_t *mutex)
{
  struct proc *p;
  int min=41;

  if(mutex == 0)
    return -1;
  if(mutex->init != 1)
    return -2;
  if(proc->mtx == 0)
    return -3;
  acquire(&ptable.lock);
  mutex->flag = 0;
  proc->mtx=0;
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->mtx == mutex && p->state == SLEEPING && min>p->nice) 
      min=p->nice;
    }
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){

    if(p->mtx == mutex&& p->state == SLEEPING && p->nice == min){
      p->state=RUNNABLE;
      break;
    }
  }
    release(&ptable.lock);
   // yield();
  
  return 0;
}
int cond_init(struct cond_t *cond)
{
  if(cond == 0)
    return -1;
  if(cond->init==1)
    return -2;
  if((cond->flag=0)!=0)
    return -3;
  cond->init=1;
  return 0;
}
int cond_wait(struct cond_t *cond, struct mutex_t *mutex)
{
  if(mutex == 0 || cond == 0)
    return -1;
  if(mutex->init != 1 || cond->init != 1)
    return -2;
  if(proc->mtx != mutex)
    return -3;
  
  proc->cnd=cond;
  if(cond->flag == 0){
    cond->flag=1;
  }
  else{
    mutex_unlock(mutex);
    acquire(&ptable.lock);
    while(1)
    {
      if(proc->cnd->flag == 0){
        release(&ptable.lock);
        mutex_lock(mutex);
        break;
      }
      sleep(proc,&ptable.lock);
    }
  }
  return 0;
}
int cond_signal(struct cond_t *cond)
{
  struct proc *p;
  int min=41;
  if(cond == 0)
    return -1;
  if(cond->init != 1)
    return -2;

  acquire(&ptable.lock);
  cond->flag=0;
  proc->cnd=0;
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->cnd == cond && p->state == SLEEPING && min>p->nice) 
      min=p->nice;
    }
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->cnd == cond && p->state == SLEEPING && p->nice == min){
      p->state=RUNNABLE;
      break;
    }
  }
    release(&ptable.lock);
 // yield();
  
  return 0;
}
