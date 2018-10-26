
#include <stdio.h>
#include <stdlib.h>

extern void work_a(void);
extern void work_b(void);
extern void work_c(void);

void main(void)
{
  printf("main start\n");
  work_a();
  work_b();
  work_c();
  printf("main end\n");
}
