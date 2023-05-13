extern int printd( int i );
int main() {
   int i;
   int x;
   for (i=0; i<10; i=i+1) {
	if (i==5){
	 printd(i);
	 }
   }
   printd(i);
   return (i+3);
}
