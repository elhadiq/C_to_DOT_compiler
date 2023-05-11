extern int printd(int f,int j);
int main() {
int i=10;
int x=1;
float f;
int a=3;
    a = x * 3 + 5;
    if(x>a) {
        printf("Hi!");
        a = x * 3 + 100;
        if(x>a) {
            printd(5);
            a = x * 3 + 100;
        }
        else {
            x = a * 3 + 100;
        }
    }
    else {
    x = a * 3 + 98;
     }
     return 0;
}
