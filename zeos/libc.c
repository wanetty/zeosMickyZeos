/*
 * libc.c 
 */

#include <libc.h>

#include <types.h>

int errno;

void itoa(int a, char *b)
{
  int i, i1;
  char c;
  
  if (a==0) { b[0]='0'; b[1]=0; return ;}
  
  i=0;
  while (a>0)
  {
    b[i]=(a%10)+'0';
    a=a/10;
    i++;
  }
  
  for (i1=0; i1<i/2; i1++)
  {
    c=b[i1];
    b[i1]=b[i-i1-1];
    b[i-i1-1]=c;
  }
  b[i]=0;
}

int strlen(char *a)
{
  int i;

 
  i=0;
  
  while (a[i]!=0) i++;
  
  return i;
}
int write(int fd,char *buffer, int size){
  //int aux = 4;
  int aux2;
  __asm__("INT $0x80;"
	 :"=a"(aux2)
	 :"b"(fd), "c"(buffer),"d"(size), "a"(4));
	 
 if(aux2 < 0){
    errno = -aux2;
    return -1;
  }
  else return aux2;
}

int gettime(){
    int aux;
    __asm__("movl $10, %%eax;"
            "INT $0x80;"
            :"=a"(aux));
    return aux;
}
void perror()
{
  char buffer[256];
  itoa(errno, buffer);
  
  write(1, buffer, sizeof(buffer));
}


