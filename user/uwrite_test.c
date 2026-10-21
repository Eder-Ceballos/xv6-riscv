#include "kernel/types.h"
#include "kernel/riscv.h"
#include "kernel/memlayout.h"
#include "user/user.h"

int
main(void)
{
  printf("antes de escribir\n");
  *(volatile int *)USYSCALL = 5;
  printf("ERROR: no murio\n");
  exit(0);
}
