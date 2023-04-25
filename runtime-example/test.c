#include <stdio.h>
#include <stdlib.h>

static int fib(int n) {
  if (n < 2)
    return n;
  else
    return fib(n - 1) + fib(n - 2);
}

int main(int argc, char *argv[]) {
  if (argc < 2)
    return EXIT_FAILURE;
  int n = atoi(argv[1]);
  int answer = fib(n);
  printf("%d\n", answer);
}
