extern int printd( int i );

int main() {
   int i;
   for (i=0; i<10; i=i+1) 
	if (i==5) break;else printd(5);
   printd(i);
}
