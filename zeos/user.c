#include <libc.h>

char buff[24];

int pid;

int add(int par1, int par2){
  int par0;
  __asm__("addl %%ebx,%%eax"
	  :"=a"(par0)
	  :"a"(par1),"b"(par2)
	  );
  return par0;}


long inner(long n)
{
	int i;
	long suma;
	suma = 0;
	for(i = 0; i < n; i++) suma = suma + i;
	return suma;
}

long outer (long n)
{
	int i;
	long acum;
	acum = 0;
	for (i = 0; i < n; i++) acum =  acum + inner(i);
	return acum;
}






int __attribute__ ((__section__(".text.main")))
  main(void)
{
	long count, acum;
	int i;
	count = 75;
	acum = 0;
	acum = outer(count);
        i = add(5, 69);
	
    /* Next line, tries to move value 0 to CR3 register. This register is a privileged one, and so it will raise an exception */
     /* __asm__ __volatile__ ("mov %0, %%cr3"::"r" (0) ); */

    
  while(1) { }
	return 0;
}
