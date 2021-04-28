#include <stdio.h>
#include "lorem.h"
#include "add/add.h"
#include "sub/sub.h"

int main(int argc, char const *argv[]) {
  printf("Hello from the world of madness\n");
  printf("%s\n", gen_random_text());
  printf("_____\n");
  printf("Test add: 3 + 4 = %d, 23 * 3 = %d\n", add(3, 4), multiply(23, 3));
  printf("_____\n");
  printf("Test sub: 132 - 23 = %d\n", sub(132, 23));
  return 0;
}