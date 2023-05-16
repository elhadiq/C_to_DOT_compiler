#include<stdio.h>
int main(){
    int i=10,j=20;
    printf("exterierur i=%d  j=%d \n",i,j);
    echange(&i,&j);
    printf("exterierur i=%d  j=%d \n",i,j);
    return 0;
}
void echange(int* i,int* j){
    int aux;
    aux=i*;
    i=j;
    j=aux;
    printf(" interieur i=%d  j=%d \n",i,j);
}