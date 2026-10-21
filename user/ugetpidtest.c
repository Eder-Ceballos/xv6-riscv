#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  printf("padre: ugetpid=%d getpid=%d\n", ugetpid(), getpid());
  int pid = fork();
  if(pid == 0){
    printf("hijo: ugetpid=%d getpid=%d\n", ugetpid(), getpid());
    exit(0);
  }
  wait(0);
  // Ver que sbrk no invade la página
  char *p = sbrk(0);
  printf("sbrk: %p\n", p);
  exit(0);
}
