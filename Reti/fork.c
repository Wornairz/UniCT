#include <stdio.h>

int main(int argc, char **argv) {
  int n = 0;
  int pid = fork();
  if (pid == 0) {
    n++;
    printf("tuo padre\n");
    printf("n=%d", n);
  } else {
    n++;
    printf("tuo figlio, pid = %d \n", pid);
    printf("n=%d", n);
  }
  return 0;
}
