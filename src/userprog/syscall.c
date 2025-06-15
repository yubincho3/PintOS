#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "devices/shutdown.h"
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"
#include "userprog/pagedir.h"
#include "userprog/process.h"

typedef int pid_t;

static void syscall_handler (struct intr_frame *);
static bool has_valid_pointer (struct intr_frame *);
static void halt (void);
static void exit (int status);
static pid_t exec (const char *cmd_line);
static int wait (pid_t pid);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f) 
{
  if (!has_valid_pointer (f))
    exit (-1);

  const int number = *(int*)f->esp;
  void const *parg = f->esp + sizeof(int);

  switch (number)
  {
  case SYS_HALT:
    halt ();
    break;
  case SYS_EXIT:
    exit (*(int*)parg);
    break;
  case SYS_EXEC:
    f->eax = exec (*(const char**)parg);
    break;
  case SYS_WAIT:
    f->eax = wait (*(pid_t*)parg);
    break;
  default:
    printf ("system call!\n");
    thread_exit ();
  }
}

static bool
has_valid_pointer (struct intr_frame *f)
{
  struct thread *cur = thread_current ();

  if (is_kernel_vaddr (f->esp) || pagedir_get_page (cur->pagedir, f->esp) == NULL)
    return false;

  int number = *(int*)f->esp;

  switch (number)
  {
  case SYS_EXIT:
  case SYS_EXEC:
  case SYS_WAIT:
    if (is_kernel_vaddr (f->esp + sizeof(int)) || pagedir_get_page (cur->pagedir, f->esp + sizeof(int)) == NULL)
      return false;
  default:
    break;
  }

  return true;
}

static void
halt (void)
{
  shutdown_power_off ();
}

static void
exit (int status)
{
  struct thread *cur = thread_current ();
  cur->exit_status = status;
  printf ("%s: exit(%d)\n", cur->name, status);
  sema_up (&cur->sema_wait);
  thread_exit ();
}

static pid_t
exec (const char *cmd_line)
{
  return process_execute (cmd_line);
}

static int
wait (pid_t pid)
{
  return process_wait (pid);
}
