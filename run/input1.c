extern int aa();extern int ac();extern int ab();
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
            printf("Hi!");
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
