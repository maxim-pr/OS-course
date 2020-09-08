#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
  int n = 9;

  int parent_id = getpid(); // id of the current process
  fork();

  if (getpid() == parent_id)
    printf("Hello from parent [%d - %d]\n", parent_id, n);
  else
    printf("Hello from child [%d - %d]\n", getpid(), n);


  return 0;
}
