extern int abo();
int koko() {



  int i,j;
  i = 45000;
  j = -123;
  printd(i+j);
  printd(45000+j);
  printd(i+123);
  printd(45000+123);
  printd(i+(j+0));
  printd((i+0)+j);
  printd((i+0)+(j+0));
  printd((i+0)+123);
  printd(45000+(j+0));
  return 0;
}
int lio() {
  int i,j;
  i = 45000;
  return 0;
}
