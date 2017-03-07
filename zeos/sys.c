/*
 * sys.c - Syscalls implementation
 */
#include <devices.h>

#include <utils.h>

#include <io.h>

#include <mm.h>
#include <errno.h>

#include <mm_address.h>

#include <sched.h>

#define LECTURA 0
#define ESCRIPTURA 1

int zeos_ticks;
int check_fd(int fd, int permissions)
{
  if (fd!=1) return EBADF;
  if (permissions!=ESCRIPTURA) return EACCES;
  return 0;
}

int sys_ni_syscall()
{
	return ENOSYS;
}

int sys_getpid()
{
	return current()->PID;
}

int sys_fork()
{
  int PID=-1;

  // creates the child process
  
  return PID;
}

void sys_exit()
{  
}
#define TAM  256

int sys_write(int fd, char *buffer, int size){
    
    int bytes = size;
    char bufferlocal[TAM];
    int error = (check_fd(fd,ESCRIPTURA));
    if (error != 0) return -error;
    else if (buffer == NULL) return -EFAULT;
    else if (size < 0) return -EINVAL; 
    
    int bytes_escritos = 0;
    while (bytes > TAM) {
	error = copy_from_user(buffer,bufferlocal,TAM);
	if (error < 0) return error;
	bytes_escritos = bytes_escritos + sys_write_console(bufferlocal,TAM);
	bytes = bytes - TAM;
	buffer += TAM;
    }
    if (bytes > 0) {
       error = copy_from_user(buffer,bufferlocal,bytes);
       if (error < 0) return error;
       bytes_escritos = bytes_escritos + sys_write_console(bufferlocal,bytes);
       bytes = bytes - TAM;
       buffer += TAM;
    }
   
    return bytes_escritos;
	
}

int sys_gettime() {
   
    return zeos_ticks;
}


    
