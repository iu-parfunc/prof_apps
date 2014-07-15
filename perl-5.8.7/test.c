#include <stdio.h>
#include <stdlib.h>

typedef struct a {
  int first;
} a;

typedef struct b {
  int second;
} b;

a* foo(a* x, b* y) {
  return x=NULL,y; 
}

int main() {

  a* x = (a*)malloc(sizeof(a));
  b* y = (b*)malloc(sizeof(b));

  foo(x, y);
  return 0;

}
