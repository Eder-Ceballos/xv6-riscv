#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  printf("inicio\n");
  vmprint();
  char *a = sbrklazy(8 * 4096);
  a[3 * 4096] = 1;
  printf("despues de tocar la pagina 3 de 8\n");
  vmprint();
  exit(0);
}
