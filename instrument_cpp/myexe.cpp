
#include <stdio.h>
#include <stdlib.h>

extern void work_a(void);
extern void work_b(void);
extern void work_c(void);

int main(int argc, char *argv[])
{
  printf("main start\n");
  work_a();
  work_b();
  work_c();
  printf("main end\n");
  return 0;
}
