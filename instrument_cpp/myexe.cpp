
#include <stdio.h>
#include <stdlib.h>
#include <vector>

extern void work_a(void);
extern void work_b(void);
extern void work_c(void);

int main(int argc, char *argv[])
{
  std::vector<int> vi;
  vi.size();
  work_c();
  return 0;
}
