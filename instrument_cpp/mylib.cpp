#include <stdio.h>
#include <stdlib.h>
#include <vector>

void work_a()
{
  printf("work_a\n");
}
void work_b()
{
  printf("work_b\n");
}
void work_c()
{
  printf("work_c\n");
  work_a();
  work_b();
  	std::vector<int> vi;
	vi.size();
}
