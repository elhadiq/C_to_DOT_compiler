extern int printd(  );

int main() {
  printd(fact(10));
  return 0;
}

int fact() {
int n;
  if ( n <= 1 )
    return 1;
  return n*fact(n-1);
}

