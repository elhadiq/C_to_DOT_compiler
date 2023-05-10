#include<stdio.h>
int main() {
  int i,j;
  i = 45000;
  j = -123;
  printf(i+j);
  printf(45000+j);
  printf(i+123);
  printf(45000+123);
  printf(i+(j+0));
  printf((i+0)+j);
  printf((i+0)+(j+0));
  printf((i+0)+123);
  printf(45000+(j+0));
  return 0;
}
