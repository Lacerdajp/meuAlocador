#include<stdio.h>
#include<stdlib.h>
#include"meuAlocador.h"
int main(){
    printf("OII");
    void *p3=Alocar(0);
    void *p4=Alocar(0);
    int diferenca=p4-p3;
    printf("diferenca: %p,%p\n",p4,p3);
    Liberar(p3);
    Liberar(p4);
    return 0;
}