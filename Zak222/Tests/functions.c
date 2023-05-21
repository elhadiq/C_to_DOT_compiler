extern int printd( int i );



int main() {
  printd(printd(fact(10)));
  return 0;
}
