#include "kernel/types.h"
#include "kernel/riscv.h"
#include "kernel/memlayout.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  // Si el proceso viene de exec(), solo comprueba su pid.
  if(argc > 1){
    int ok = ugetpid() == getpid();
    printf("exec: ugetpid=%d getpid=%d\n", ugetpid(), getpid());
    exit(ok ? 0 : 1);
  }

  int ok = 1;
  printf("padre: ugetpid=%d getpid=%d\n", ugetpid(), getpid());
  if(ugetpid() != getpid()) ok = 0;

  // Hijos con fork
  for(int i = 0; i < 8; i++){
    int pid = fork();
    if(pid == 0)
      exit(ugetpid() == getpid() ? 0 : 1);
    int st;
    wait(&st);
    if(st != 0) ok = 0;
  }
  printf("hijos: OK si todos coinciden\n");

  // exec: el nuevo programa debe ver el pid correcto
  int pid = fork();
  if(pid == 0){
    char *args[] = { argv[0], "x", 0 };
    exec(argv[0], args);
    exit(2);
  }
  int st;
  wait(&st);
  if(st != 0) ok = 0;

  // Heap: crecer con sbrklazy hasta el límite; nunca debe pasar de USYSCALL
  pid = fork();
  if(pid == 0){
    while(sbrklazy(1 << 30) != (char *)-1)
      ;
    while(sbrklazy(PGSIZE) != (char *)-1)
      ;
    if((uint64)sbrklazy(0) > USYSCALL) exit(3);
    exit(ugetpid() == getpid() ? 0 : 4);
  }
  wait(&st);
  if(st != 0) ok = 0;

  printf(ok ? "RESULTADO: PARTE A OK\n" : "RESULTADO: PARTE A FALLO\n");
  exit(ok ? 0 : 1);
}
